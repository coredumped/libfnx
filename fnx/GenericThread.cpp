//
//  GenericThread.cpp
//
//  Created by Juan V. Guerrero on 9/26/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include "GenericThread.h"
#include "MTLogger.h"

namespace fnx {
	GenericThread::GenericThread(){

	}
	
	GenericThread::~GenericThread(){
		
	}
	
	void GenericThread::onStart(){
#ifdef DEBUG
		fnx::Log << "DEBUG: Starting thread " << fnx::NL;
#endif
	}
	
	void GenericThread::operator()(){
#ifdef DEBUG
		fnx::Log << "DEBUG: Look I am thread running in the background :-)" << fnx::NL;
#endif
	}
	
	void GenericThread::onFinish(){
#ifdef DEBUG
		fnx::Log << "DEBUG: Finishing thread " << fnx::NL;
#endif
	}

}
