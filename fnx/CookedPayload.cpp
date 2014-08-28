//
//  CookedPayload.cpp
//  fnx
//
//  Created by Juan Guerrero on 8/27/14.
//  Copyright (c) 2014 fn(x) Software. All rights reserved.
//

#include "CookedPayload.h"

namespace fnx {
    CookedPayload::CookedPayload() {
        
    }
    CookedPayload::CookedPayload(NotificationPayload::DeviceType _deviceType, const std::string &_devtoken, const std::string &_jsonRep) {
        devToken = _devtoken;
        jsonPayload = _jsonRep;
        deviceType = _deviceType;
    }

}