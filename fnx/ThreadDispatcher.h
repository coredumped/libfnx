//
//  ThreadDispatcher.h
//
//  Created by Juan V. Guerrero on 9/26/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#ifndef fnx_ThreadDispatcher_h
#define fnx_ThreadDispatcher_h
#include <string>
#include <fnx/fnxconfig.h>
#include <fnx/GenericThread.h>

namespace fnx {
	class ThreadDispatcher {
	private:
	protected:
	public:
		/** Starts a background execution of a GenericThread object */
		static void start(GenericThread &gt, size_t stackSize = 0);
	};
	
	class ThreadExecutionException {
	private:
		std::string errmsg;
	public:
		ThreadExecutionException();
		ThreadExecutionException(const std::string &_errmsg);
		std::string message();
	};
}


#endif
