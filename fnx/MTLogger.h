//
//  MTLogger.h
//
//  Created by Juan V. Guerrero on 10/12/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#ifndef fnx_MTLogger_h
#define fnx_MTLogger_h
#include <fnx/fnxconfig.h>
#include <fnx/Mutex.h>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <fstream>

namespace fnx {
	class MTLogger {
	private:
		Mutex m;
		size_t writtenBytes;
		size_t maxLogSize;
		std::string logPath;
	protected:
		std::map<pthread_t, std::string> streamMap;
		std::ofstream outputStream;
		void initLogline();
		std::string tag;
	public:
		MTLogger();
		void open(const std::string &path);
		void setTag(const std::string &_tag);
		
		MTLogger &operator<<(int val);
		MTLogger &operator<<(long val);
		MTLogger &operator<<(const std::string &s);
		MTLogger &operator<<(double d);
		
		void flush();
	};
		
	extern MTLogger Log;
	
	extern std::string NL;
}


#endif
