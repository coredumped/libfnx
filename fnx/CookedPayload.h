//
//  CookedPayload.h
//  fnx
//
//  Created by Juan Guerrero on 8/27/14.
//  Copyright (c) 2014 fn(x) Software. All rights reserved.
//

#ifndef __fnx__CookedPayload__
#define __fnx__CookedPayload__
#include<string>
#include <map>
#include <fnx/fnxconfig.h>
#include <fnx/NotificationPayload.h>

namespace fnx {
    class CookedPayload {
    public:
        std::string devToken;
        std::string jsonPayload;
        NotificationPayload::DeviceType deviceType;
        CookedPayload();
        CookedPayload(NotificationPayload::DeviceType _deviceType, const std::string &_devtoken, const std::string &_jsonRep);
        
    };
}


#endif
