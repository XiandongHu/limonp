/*
 * https://github.com/chenshuo/muduo/blob/master/muduo/base/Condition.h
 */

#ifndef LIMONP_CONDITION_HPP
#define LIMONP_CONDITION_HPP

#include "MutexLock.hpp"

namespace Limonp
{
    class Condition : NonCopyable
    {
        public:
            explicit Condition(MutexLock& mutex)
                : _mutex(mutex)
            {
                LIMONP_CHECK(pthread_cond_init(&_pcond, NULL));
            }

            ~Condition()
            {
                LIMONP_CHECK(pthread_cond_destroy(&_pcond));
            }

            void wait()
            {
                LIMONP_CHECK(pthread_cond_wait(&_pcond, _mutex.getPthreadMutex()));
            }

            void notify()
            {
                LIMONP_CHECK(pthread_cond_signal(&_pcond));
            }

            void notifyAll()
            {
                LIMONP_CHECK(pthread_cond_broadcast(&_pcond));
            }

        private:
            MutexLock& _mutex;
            pthread_cond_t _pcond;
    };

}

#endif
