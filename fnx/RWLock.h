//
//  RWLock.h
//
//  Created by Juan Guerrero on 7/9/12.
//  Copyright (c) 2012 fn(x) Software. All rights reserved.
//

#ifndef fnx_Sucker_RWLock_h
#define fnx_Sucker_RWLock_h
#include <pthread.h>
#include <fnx/GenericException.h>

namespace fnx {
	
	class RWLock {
	private:
		pthread_rwlock_t theLock;
	protected:
	public:
		RWLock();
		~RWLock();
		void readLock();
		void writeLock();
		void unlock();
	};
}

#endif
