//
//  GenericException.h
//
//  Created by Juan V. Guerrero on 9/30/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#ifndef fnx_GenericException_h
#define fnx_GenericException_h
#include <string>

namespace fnx {
	
	class GenericException {
	protected:
		std::string errmsg;
	public:
		GenericException();
		GenericException(const std::string &_errmsg);
		std::string message();
	};
}

#endif
