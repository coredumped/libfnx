//
//  PendingNotificationStore.cpp
//
//  Created by Juan Guerrero on 4/17/12.
//  Copyright (c) 2012 fn(x) Software. All rights reserved.
//
#include "PendingNotificationStore.h"
#include "UtilityFunctions.h"
#include "GenericException.h"
#include <iostream>
#include <sqlite3.h>
#ifndef DEFAULT_PENDING_NOTIFICATION_DATAFILE
#define DEFAULT_PENDING_NOTIFICATION_DATAFILE "pending_queue.db"
#endif
#ifndef DEFAULT_PENDING_NOTIFICATION_TABLE
#define DEFAULT_PENDING_NOTIFICATION_TABLE "pending_queue"
#endif
#ifndef DEFAULT_PAYLOAD_SENT_TABLE
#define DEFAULT_PAYLOAD_SENT_TABLE "sent_notifications"
#endif

namespace fnx {

	static const char *qTable = DEFAULT_PENDING_NOTIFICATION_TABLE;
	static const char *sentTable = DEFAULT_PAYLOAD_SENT_TABLE;
	sqlite3 *sDB = NULL;
	
	static void sqlQuote(std::string &_return, const std::string origSQL){
		for (size_t i = 0; i < origSQL.size(); i++) {
			if (origSQL[i] == '\'') {
				_return.append("''");
			}
			else {
				_return.append(1, origSQL[i]);
			}
		}
	}
	
	static sqlite3 *connect2NotifDB(){
		sqlite3 *qDB = NULL;
		//if(sqlite3_open(DEFAULT_PENDING_NOTIFICATION_DATAFILE, &qDB) != SQLITE_OK){
		if(sqlite3_open_v2(DEFAULT_PENDING_NOTIFICATION_DATAFILE, &qDB, SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE|SQLITE_OPEN_FULLMUTEX, NULL) != SQLITE_OK){
			fnx::Log << "Unable to open " << DEFAULT_PENDING_NOTIFICATION_DATAFILE << " datafile: " << sqlite3_errmsg(qDB) << fnx::NL;
			throw GenericException(sqlite3_errmsg(qDB));
		}
		//Create preferences table if it does not exists
		if(!fnx::tableExists(qDB, qTable)){
			std::stringstream createCmd;
			char *errmsg;
			createCmd << "CREATE TABLE " << qTable << " (";
			createCmd << "id		INTEGER PRIMARY KEY,";
			createCmd << "devtoken	TEXT,";
			createCmd << "message	TEXT,";
			createCmd << "sound		TEXT,";
			createCmd << "badge		INTEGER,";
            createCmd << "devtype	INTEGER";
			createCmd << ")";
			if(sqlite3_exec(qDB, createCmd.str().c_str(), 0, 0, &errmsg) != SQLITE_OK){
				fnx::Log << "Unable to create pending notifications table: " << errmsg << fnx::NL;
				throw GenericException(errmsg);
			}
		}
		if(!fnx::tableExists(qDB, sentTable)){
			std::stringstream createCmd;
			char *errmsg;
			createCmd << "CREATE TABLE " << sentTable << " (";
			createCmd << "id		INTEGER PRIMARY KEY,";
			createCmd << "devtoken	TEXT,";
			createCmd << "message	TEXT,";
			createCmd << "tstamp	INTEGER,";
			createCmd << "errorcode	INTEGER,";
            createCmd << "devtype	INTEGER";
			createCmd << ")";
			if(sqlite3_exec(qDB, createCmd.str().c_str(), 0, 0, &errmsg) != SQLITE_OK){
				fnx::Log << "Unable to create pending notifications table: " << errmsg << fnx::NL;
				throw GenericException(errmsg);
			}
		}
		return qDB;
	}
	
	//static Mutex __pM;
	void PendingNotificationStore::savePayloads(SharedQueue<NotificationPayload> *nQueue){
		if(nQueue == 0) return;
		if(sDB == NULL) sDB = connect2NotifDB();
		NotificationPayload payload;
		int i = 1000;
		while (nQueue->extractEntry(payload)) {
			std::stringstream insCmd;
			char *errmsg;
			insCmd << "INSERT INTO " << qTable << " (id, devtoken, message, sound, badge, devtype) VALUES (";
			insCmd << (i++) << ", '" << payload.deviceToken() << "', ";
			insCmd << "'" << payload.message() << "', '" << payload.soundName() << "', " << payload.badge() << "," << (int)payload.devType() << ")";
			if (sqlite3_exec(sDB, insCmd.str().c_str(), 0, 0, &errmsg) != SQLITE_OK) {
				fnx::Log << "Unable to add notification payload to persistent queue(" << insCmd.str() << "): " << errmsg << fnx::NL;
			}
			fnx::Log << " * Saving notification for device: " << payload.deviceToken() << fnx::NL;
		}
	}
	
	void PendingNotificationStore::saveSentPayload(const std::string &devToken, const std::string &payload, uint32_t _id){
		if(sDB == NULL) sDB = connect2NotifDB();
		std::stringstream insCmd;
		std::string quotedPayload;
		char *errmsg;
		sqlQuote(quotedPayload, payload);
		insCmd << "INSERT INTO " << sentTable << " (id, devtoken, message, tstamp) VALUES (";
		insCmd << _id << ", '" << devToken << "', ";
		insCmd << "'" << quotedPayload << "'," << time(0) << ")";
		if (sqlite3_exec(sDB, insCmd.str().c_str(), 0, 0, &errmsg) != SQLITE_OK) {
			fnx::Log << "Unable to add notification payload to persistent queue(" << insCmd.str() << "): " << errmsg << fnx::NL;
		}
	}
	
	void PendingNotificationStore::setSentPayloadErrorCode(uint32_t _id, int errorCode){
		if(sDB == NULL) sDB = connect2NotifDB();
		std::stringstream insCmd;
		char *errmsg;
		insCmd << "UPDATE " << sentTable << " SET errorcode=" << errorCode << " WHERE id=" << _id;
		if (sqlite3_exec(sDB, insCmd.str().c_str(), 0, 0, &errmsg) != SQLITE_OK) {
			fnx::Log << "Unable to set payload error code (" << insCmd.str() << "): " << errmsg << fnx::NL;
		}		
	}
	
	void PendingNotificationStore::eraseOldPayloads(){
		if(sDB == NULL) sDB = connect2NotifDB();
		std::stringstream insCmd;
		char *errmsg;
		insCmd << "DELETE FROM " << sentTable << " WHERE tstamp < " << time(0) - 86500;
		if (sqlite3_exec(sDB, insCmd.str().c_str(), 0, 0, &errmsg) != SQLITE_OK) {
			fnx::Log << "Unable to erase old payloads (" << insCmd.str() << "): " << errmsg << fnx::NL;
		}		
	}
	
	bool PendingNotificationStore::getDeviceTokenFromMessage(std::string &devToken, uint32_t _id){
		bool ret = false;
		if(sDB == NULL) sDB = connect2NotifDB();
		std::stringstream sqlCmd;
		sqlite3_stmt *statement;
		char *szTail;
		sqlCmd << "SELECT devtoken FROM " << sentTable << " where id=" << _id;
		if(sqlite3_prepare_v2(sDB, sqlCmd.str().c_str(), (int)sqlCmd.str().size(), &statement, (const char **)&szTail) == SQLITE_OK){
			if (sqlite3_step(statement) == SQLITE_ROW) {
				devToken = (const char *)sqlite3_column_text(statement, 0);
				ret = true;
			}
			sqlite3_finalize(statement);
		}
		else {
			const char *errmsg = sqlite3_errmsg(sDB);
			fnx::Log << "Unable to retrieve device token from notification with id=" << (int)_id << " (" << sqlCmd.str() << ") due to: " << errmsg << fnx::NL;
		}
		return ret;
	}
	
	void PendingNotificationStore::loadPayloads(SharedQueue<NotificationPayload> *nQueue){
		if(sDB == NULL) sDB = connect2NotifDB();
		std::stringstream sqlCmd;
		sqlite3_stmt *statement;
		char *szTail;
		sqlCmd << "SELECT devtoken,message,sound,badge,devtype FROM " << qTable;
		if(sqlite3_prepare_v2(sDB, sqlCmd.str().c_str(), (int)sqlCmd.str().size(), &statement, (const char **)&szTail) == SQLITE_OK){
			while (sqlite3_step(statement) == SQLITE_ROW) {
				const char *tok = (const char *)sqlite3_column_text(statement, 0);
				const char *msg = (const char *)sqlite3_column_text(statement, 1);
				const char *snd = (const char *)sqlite3_column_text(statement, 2);
				int badge = sqlite3_column_int(statement, 3);
                int devtype = sqlite3_column_int(statement, 4);
				fnx::Log << " * Loading notification for device: " << tok << fnx::NL;
				NotificationPayload payload((NotificationPayload::DeviceType)devtype, tok, msg, badge, snd);
				nQueue->add(payload);
			}
			sqlite3_finalize(statement);
		}
		else {
			const char *errmsg = sqlite3_errmsg(sDB);
			fnx::Log << "Unable to retrieve notification payloads from last crash or app shutdown (" << sqlCmd.str() << ") due to: " << errmsg << fnx::NL;
		}
		//Remove data
		char *errmsg;
		std::stringstream delCmd;
		delCmd << "DELETE FROM " << qTable;
		if (sqlite3_exec(sDB, delCmd.str().c_str(), 0, 0, &errmsg) != SQLITE_OK) {
			fnx::Log << "Unable to add notification payload to persistent queue(" << delCmd.str() << "): " << errmsg << fnx::NL;
		}
	}
    
    void PendingNotificationStore::loadSentPayloadsSince(SharedQueue<CookedPayload> *nQueue, uint32_t _start_id) {
        if(sDB == NULL) sDB = connect2NotifDB();
        std::stringstream sqlCmd;
        sqlite3_stmt *statement;
        char *szTail;
        sqlCmd << "SELECT devtoken,message,devtype FROM " << sentTable << " WHERE id>=" << _start_id;
        if(sqlite3_prepare_v2(sDB, sqlCmd.str().c_str(), (int)sqlCmd.str().size(), &statement, (const char **)&szTail) == SQLITE_OK){
            while (sqlite3_step(statement) == SQLITE_ROW) {
                const char *tok = (const char *)sqlite3_column_text(statement, 0);
                const char *msg = (const char *)sqlite3_column_text(statement, 1);
                int devtype = sqlite3_column_int(statement, 2);
                fnx::Log << " * Resending notification to device: " << tok << fnx::NL;
                CookedPayload payload((NotificationPayload::DeviceType)devtype, tok, msg);
                nQueue->add(payload);
            }
            sqlite3_finalize(statement);
        }
        else {
            const char *errmsg = sqlite3_errmsg(sDB);
            fnx::Log << "Unable to retrieve notification payloads from last crash or app shutdown (" << sqlCmd.str() << ") due to: " << errmsg << fnx::NL;
        }
    }
}