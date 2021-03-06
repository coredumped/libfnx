//
//  Mutex.h
//
//  Created by Juan V. Guerrero on 9/25/11.
//  Copyright (c) 2011 fn(x) Software. All rights reserved.
//

#ifndef fnx_Mutex_h
#define fnx_Mutex_h
#include <pthread.h>
#include <fnx/fnxconfig.h>
#include <fnx/GenericException.h>
namespace fnx {
    //Encapsulates a POSIX threads mutual exclusion device
    class Mutex {
    private:
        pthread_mutex_t theMutex;
        pthread_mutexattr_t attrs;
        char *lFile;
        int lLine;
    public:
        Mutex();
        ~Mutex();
        void lock();
        void lockWithInfo(const char *_srcFile = __FILE__, int _srcLine = __LINE__);
        void unlock();
    };
    
    class MutexLockException : public GenericException {
    public:
        std::string srcFile;
        int srcLine;
        MutexLockException();
        MutexLockException(const std::string &_errmsg);
        MutexLockException(const std::string &_errmsg, const char *_srcFile, int _srcLine);
    };
}

#endif
