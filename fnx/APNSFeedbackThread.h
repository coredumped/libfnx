//
//  APNSFeedbackThread.h
//
//  Created by Juan Guerrero on 4/15/12.
//  Copyright (c) 2012 fn(x) Software. All rights reserved.
//

#ifndef fnx_APNSFeedbackThread_h
#define fnx_APNSFeedbackThread_h
#include <fnx/fnxconfig.h>
#include <fnx/GenericThread.h>
#include <fnx/APNSNotificationThread.h>
#include <fnx/SharedVector.h>
#include <fnx/MTLogger.h>
#include <set>

namespace fnx {
	class APNSFeedbackThread : public GenericThread {
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
		
		std::string _keyPath;
		std::string _certPath;
		std::string _certPassword;
		
	protected:
		bool sslInitComplete;
		void initSSL();
	public:
		APNSFeedbackThread();
		void setKeyPath(const std::string &keyPath);
		void setCertPath(const std::string &certPath);
		void setCertPassword(const std::string &certPwd);
		~APNSFeedbackThread();
		void operator()();
		void useForProduction();
        int checkInterval;
		
		static void invalidTokens(std::set<std::string> &devTokens);
		static bool isTokenInvalid(const std::string &devToken);
	};
	
	extern MTLogger fdbckLog;
}

#endif
