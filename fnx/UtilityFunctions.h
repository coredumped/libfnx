//
//  UtilityFunctions.h
//
//  Created by Juan V. Guerrero on 9/29/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#ifndef fnx_UtilityFunctions_h
#define fnx_UtilityFunctions_h
#include <string>
#include <vector>
#include <sqlite3.h>
#ifdef __linux__
#include <stdint.h>
#endif
#include <fnx/fnxconfig.h>

namespace fnx {
    
	void url_encode(std::string &theString);
    namespace ios {
        /** Converts an iOS device token to a binary representation.
         *  @param devTokenString The device token to transform.
         *  @param binaryDevToken A reference to the string that is to receive the binary representation. */
        void devToken2Binary(std::string devTokenString, std::string &binaryDevToken);
        /** Convert an iOS device token from its binary representation to hexadecimal form.
            @param devToken A reference to a string that will receive the hexadecimal representation.
            @param binaryToken A 32 bit integer containing the device token binary representation. */
        void binary2DevToken(std::string &devToken, uint32_t binaryToken);
    }
    
	void nltrim(std::string &s);
	
	void splitString(std::vector<std::string> &_return, const std::string &theString, const std::string &delim);
    bool tableExists(sqlite3 *dbConn, const std::string &tablename);
}

#endif
