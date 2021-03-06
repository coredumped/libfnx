//
//  GenericException.h
//
//  Created by Juan V. Guerrero on 9/30/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#ifndef fnx_GenericException_h
#define fnx_GenericException_h
#include <string>
#include <fnx/fnxconfig.h>

namespace fnx {
	
    class GenericException {
    protected:
        std::string errmsg;
    public:
        GenericException();
        GenericException(const std::string &_errmsg);
        std::string message();
    };
    
    /** Exception thrown whenever we received an error response from a remote server */
    class HTTPException {
    private:
        int code;
        std::string msg;
    public:
        HTTPException();
        HTTPException(int _code, const std::string &_msg);
        int errorCode();
        std::string errorMessage();
    };
}

#endif
