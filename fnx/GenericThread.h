//
//  GenericThread.h
//
//  Created by Juan V. Guerrero on 9/26/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#ifndef fnx_GenericThread_h
#define fnx_GenericThread_h
#include"Mutex.h"
#include<string>

namespace fnx {
	class GenericThread {
	private:
	protected:
	public:
		long threadid;
		/** Tells wheter the thread is still running */
		fnx::AtomicFlag isRunning;
		GenericThread();
		virtual ~GenericThread();
		/** This method is called before your thread starts running */
		virtual void onStart();
		/** Override this method with the code you want to execute concurrently. */
		virtual void operator()();
		/** This method is called after your thread has finished executing */
		virtual void onFinish();
	};
	
}

#endif
