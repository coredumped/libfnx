//
//  NotificationPayload.cpp
//
//  Created by Juan V. Guerrero on 9/29/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//
#include "NotificationPayload.h"
#include "UtilityFunctions.h"
#include "GenericException.h"
#include <iostream>
#include <sstream>
#ifndef MAXPAYLOAD_SIZE
#define MAXPAYLOAD_SIZE 256
#endif

namespace fnx {
	
	static void msg_encode(std::string &theMsg){
		std::string newString;
		for (size_t i = 0; i < theMsg.size(); i++) {
			if (theMsg[i] == '\n') {
				newString.append("\\n");
			}
			else if (theMsg[i] == '\r') {
				newString.append("\\r");
			}
			else if (theMsg[i] == '\t') {
				newString.append("\\t");
			}
			else if (theMsg[i] == '\"') {
				newString.append("\\\"");
			}
			else if (theMsg[i] == '\\') {
				newString.append("\\\\");
			}
			else if (theMsg[i] == '\'') {
				newString.append("\\'");
			}
			else {
				char tbuf[2] = { theMsg[i], 0x00};
				newString.append(tbuf);
			}
		}
		theMsg = newString;
	}

	NotificationPayload::NotificationPayload(){
		_badgeNumber = 1;
		attempts = 0;
	}
	
	NotificationPayload::NotificationPayload(DeviceType devType, const std::string &devToken_, const std::string &_message, int badgeNumber, const std::string &sndName){
		msg = _message;
		_soundName = sndName;
		devToken = devToken_;
		_badgeNumber = badgeNumber;
		attempts = 0;
        deviceType = devType;
		build();
	}
    
	NotificationPayload::NotificationPayload(const NotificationPayload &n){
		msg = n.msg;
		_soundName = n._soundName;
		devToken = n.devToken;
		_badgeNumber = n._badgeNumber;
        deviceType = n.deviceType;
        metadata = n.metadata;
		build();
		attempts = n.attempts;
	}
	
	NotificationPayload::~NotificationPayload(){
		
	}
    
    void NotificationPayload::iosBuild() {
		std::stringstream jsonbuilder;
		std::string encodedMsg = msg;
		msg_encode(encodedMsg);
		jsonbuilder << "{";
		jsonbuilder << "\"aps\":";
		jsonbuilder << "{";
		jsonbuilder << "\"alert\":\"" << encodedMsg << "\",";
		jsonbuilder << "\"sound\":\"" << _soundName << "\"";
		if(_badgeNumber > 0) jsonbuilder << ",\"badge\":" << _badgeNumber;
		jsonbuilder << "}";
        //Begin metadata insert
        for (std::map<std::string, std::string>::iterator iter = metadata.begin(); iter != metadata.end(); iter++) {
            jsonbuilder << ",\"" << iter->first << "\":\"" << iter->second << "\"";
        }
        //End metadata insert
		jsonbuilder << "}";
		if (jsonbuilder.str().size() > MAXPAYLOAD_SIZE) {
			jsonbuilder.str(std::string());
			jsonbuilder << "{";
			jsonbuilder << "\"aps\":";
			jsonbuilder << "{";
			jsonbuilder << "\"sound\":\"" << _soundName << "\"";
			if(_badgeNumber > 0) jsonbuilder << ",\"badge\":" << _badgeNumber;
			jsonbuilder << "}";
			jsonbuilder << "}";
            
			size_t maxMsgLength = jsonbuilder.str().size() - 3;
			jsonbuilder.str(std::string());
			jsonbuilder << "{";
			jsonbuilder << "\"aps\":";
			jsonbuilder << "{";
			jsonbuilder << "\"alert\":\"" << encodedMsg.substr(0, 252 - maxMsgLength) << "...\",";
			jsonbuilder << "\"sound\":\"" << _soundName << "\"";
			if(_badgeNumber > 0) jsonbuilder << ",\"badge\":" << _badgeNumber;
			jsonbuilder << "}";
            //Begin metadata insert
            for (std::map<std::string, std::string>::iterator iter = metadata.begin(); iter != metadata.end(); iter++) {
                jsonbuilder << ",\"" << iter->first << "\":\"" << iter->second << "\"";
            }
            //End metadata insert
			jsonbuilder << "}";
		}
		msgCloudRepresentation = jsonbuilder.str();
        
    }
    
    void NotificationPayload::androidBuild() {
        throw GenericException("Unable to build Android notification payloads, the functionality has not been implemented.");
    }
	
	void NotificationPayload::build(){
        switch (deviceType) {
            case IOS:
                iosBuild();
                break;
            case ANDROID:
                androidBuild();
                break;
            default:
                throw GenericException("Unable to build notification payload for unidentified device type. Current supported device types are IOS and ANDROID only.");
                break;
        }
	}
	
	const std::string &NotificationPayload::toCloudFormat() const {
		return msgCloudRepresentation;
	}
	
	std::string &NotificationPayload::soundName(){
		return _soundName;
	}

	const std::string &NotificationPayload::soundName() const {
		return _soundName;
	}
	
	std::string &NotificationPayload::message(){
		return msg;
	}

	std::string &NotificationPayload::deviceToken(){
		return devToken;
	}
		
	int NotificationPayload::badge(){
		return _badgeNumber;
	}
    
    NotificationPayload::DeviceType NotificationPayload::devType() {
        return deviceType;
    }
    
    void NotificationPayload::setMetadata(const std::map<std::string, std::string> &meta) {
        metadata = meta;
        build();
    }
}
