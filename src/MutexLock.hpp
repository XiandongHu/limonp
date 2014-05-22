#ifndef LIMONP_MUTEX_LOCK_HPP
#define LIMONP_MUTEX_LOCK_HPP

#include <pthread.h>
#include "NonCopyable.hpp"
#include "HandyMacro.hpp"

namespace Limonp
{
    class MutexLock: NonCopyable
    {
        private:
            pthread_mutex_t _mutex;
        public:
            pthread_mutex_t* getPthreadMutex()
            {
                return &_mutex;
            }
        public:
            MutexLock()
            {
                LIMONP_CHECK(pthread_mutex_init(&_mutex, NULL));
            }
            ~MutexLock()
            {
                LIMONP_CHECK(pthread_mutex_destroy(&_mutex));
            }
        private:
            void lock()
            {
                LIMONP_CHECK(pthread_mutex_lock(&_mutex));
            }
            void unlock()
            {
                LIMONP_CHECK(pthread_mutex_unlock(&_mutex));
            }
            friend class MutexLockGuard;
    };
    class MutexLockGuard: NonCopyable
    {
        public:
            explicit MutexLockGuard(MutexLock & mutex)
                : _mutex(mutex)
            {
                _mutex.lock();
            }
            ~MutexLockGuard()
            {
                _mutex.unlock();
            }
        private:
            MutexLock & _mutex;
    };
#define MutexLockGuard(x) assert(false);
}

#endif
