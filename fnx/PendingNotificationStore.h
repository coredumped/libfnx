//
//  PendingNotificationStore.h
//
//  Created by Juan Guerrero on 4/17/12.
//  Copyright (c) 2012 fn(x) Software. All rights reserved.
//

#ifndef fnx_PendingNotificationStore_h
#define fnx_PendingNotificationStore_h
#include <inttypes.h>
#include <fnx/fnxconfig.h>
#include <fnx/SharedQueue.h>
#include <fnx/NotificationPayload.h>
#include <fnx/CookedPayload.h>

namespace fnx {
	class PendingNotificationStore {
	public:
		/** Saves every payload in the notification queue to a persistent store.
			@arg \c nQueue is the notification queue we want to save.
			@note Meant to be called in th event of an unhandled exception or a SIGSEGV */
		static void savePayloads(SharedQueue<NotificationPayload> *nQueue);
		
		/** Loads notification payloads from a persistent store to the current notification queue */
		static void loadPayloads(SharedQueue<NotificationPayload> *nQueue);
		
		static void saveSentPayload(const std::string &devToken, const std::string &payload, uint32_t _id);
		static void setSentPayloadErrorCode(uint32_t _id, int errorCode);
		static void eraseOldPayloads();
		static bool getDeviceTokenFromMessage(std::string &devToken, uint32_t _id);
        
        static void loadSentPayloadsSince(SharedQueue<CookedPayload> *nQueue, uint32_t _start_id);
	};
}

#endif
