//
//  APNSNotificationThread.h
//
//  Created by Juan V. Guerrero on 9/26/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#ifndef fnx_APNSNotificationThread_h
#define fnx_APNSNotificationThread_h
#include <fnx/GenericThread.h>
#include <fnx/SharedQueue.h>
#include <fnx/NotificationPayload.h>
#include <fnx/GenericException.h>
#include <string>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <fnx/MTLogger.h>



namespace fnx {
	
	extern MTLogger APNSLog;
	
	class SSLException : public GenericException {
	private:
	protected:
		typedef enum {
			SSLOperationAny,
			SSLOperationRead,
			SSLOperationWrite
		}  SSLOperation;
		int sslErrorCode;
		SSLOperation currentOperation;
	public:
		SSLException();
		SSLException(SSL *sslConn, int sslStatus, const std::string &_derrmsg = "");
		int errorCode();
	};
	
	class APNSNotificationThread : public GenericThread {
	private:
		SSL_CTX *sslCTX;
		SSL *apnsConnection;
		void connect2APNS();
		void ifNotConnectedToAPNSThenConnect();
		void disconnectFromAPNS();
		bool _useSandbox;
		
		int _socket;
		struct sockaddr_in _server_addr;
		struct hostent *_host_info;
		int waitTimeBeforeReconnectToAPNS;
		std::map<std::string, std::string> devTokenCache;
		int maxNotificationsPerBurst;
		int maxBurstPauseInterval;
		int maxConnectionInterval;
		
		std::string _keyPath;
		std::string _certPath;
		std::string _certPassword;

	protected:
		bool sslInitComplete;
		void initSSL();
		void notifyTo(const std::string &devToken, NotificationPayload &msg);
	public:
		AtomicFlag warmingUP;
		SharedQueue<NotificationPayload> *notificationQueue;
		APNSNotificationThread();
		void setKeyPath(const std::string &keyPath);
		void setCertPath(const std::string &certPath);
		void setCertPassword(const std::string &certPwd);
		~APNSNotificationThread();
		void operator()();
		void useForProduction();
		
		void triggerSimultanousReconnect();
		
		AtomicFlag stopExecution;
	};
	
}
#endif
