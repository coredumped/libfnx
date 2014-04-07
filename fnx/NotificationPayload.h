//
//  NotificationPayload.h
//
//  Created by Juan V. Guerrero on 9/29/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#ifndef fnx_NotificationPayload_h
#define fnx_NotificationPayload_h
#include<string>
#include <map>
#include <fnx/fnxconfig.h>

namespace fnx {
	class NotificationPayload {
    public:
        enum DeviceType {
            IOS,
            ANDROID
        };
	private:
        void iosBuild();
        void androidBuild();
		void build();
	protected:
		std::string _soundName;
		std::string msg;
		std::string devToken;
		int _badgeNumber;
		std::string msgCloudRepresentation;
        std::map<std::string, std::string> metadata;
        DeviceType deviceType;
	public:
		NotificationPayload();
		NotificationPayload(DeviceType devType, const std::string &devToken_, const std::string &_message, int badgeNumber = 1, const std::string &sndName = "pmm.caf");
		NotificationPayload(const NotificationPayload &n);
		~NotificationPayload();
		const std::string &toCloudFormat() const;
		std::string &soundName();
		const std::string &soundName() const;
		std::string &message();
		std::string &deviceToken();
		int badge();
		int attempts;
        DeviceType devType();
        void setMetadata(const std::map<std::string, std::string> &meta);
	};
}



#endif
