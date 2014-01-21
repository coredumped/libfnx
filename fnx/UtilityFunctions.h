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

namespace fnx {

	void url_encode(std::string &theString);
	void devToken2Binary(std::string devTokenString, std::string &binaryDevToken);
	void binary2DevToken(std::string &devToken, uint32_t binaryToken);
		
	void nltrim(std::string &s);
	bool tableExists(sqlite3 *dbConn, const std::string &tablename);
	
	void splitString(std::vector<std::string> &_return, const std::string &theString, const std::string &delim);
}

#endif
