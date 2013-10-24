/************************************
 * file enc : utf8
 * author   : wuyanyi09@gmail.com
 ************************************/
#ifndef CPPCOMMON_LOGGER_H
#define CPPCOMMON_LOGGER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include "file_functs.h"
#include "str_functs.h"
#include "typedefs.h"

#define LogDebug(fmt, ...) Logger::LoggingF(LL_DEBUG, __FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LogInfo(fmt, ...) Logger::LoggingF(LL_INFO, __FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LogWarn(fmt, ...) Logger::LoggingF(LL_WARN, __FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LogError(fmt, ...) Logger::LoggingF(LL_ERROR, __FILE__, __LINE__, fmt, ## __VA_ARGS__)
#define LogFatal(fmt, ...) Logger::LoggingF(LL_FATAL, __FILE__, __LINE__, fmt, ## __VA_ARGS__)


namespace CPPCOMMON
{
    using namespace std;
    enum {LL_DEBUG = 0, LL_INFO = 1, LL_WARN = 2, LL_ERROR = 3, LL_FATAL = 4, LEVEL_ARRAY_SIZE = 5, CSTR_BUFFER_SIZE = 1024};
    static const char * LOG_LEVEL_ARRAY[LEVEL_ARRAY_SIZE]= {"DEBUG","INFO","WARN","ERROR","FATAL"};
    static const char * LOG_FORMAT = "%s %s:%d %s %s\n";
    static const char * LOG_TIME_FORMAT = "%Y-%m-%d %H:%M:%S";

    class Logger
    {
        public:
            static bool Logging(uint level, const string& msg, const char* fileName, int lineNo)
            {

                return Logging(level, msg.c_str(), fileName, lineNo);
            }
            static bool Logging(uint level, const char * msg, const char* fileName, int lineNo)
            {
                if(level > LL_FATAL)
                {
                    cerr<<"level's value is out of range"<<endl;
                    return false;
                }
                char buf[CSTR_BUFFER_SIZE];
                time_t timeNow;
                time(&timeNow);
                size_t ret = strftime(buf, sizeof(buf), LOG_TIME_FORMAT, localtime(&timeNow));
                if(0 == ret)
                {
                    fprintf(stderr, "stftime failed.\n");
                    return false;
                }
                if(level >= LL_WARN)
                {
                    fprintf(stderr, LOG_FORMAT, buf, fileName, lineNo,LOG_LEVEL_ARRAY[level], msg);
                }
                else
                {
                    fprintf(stdout, LOG_FORMAT, buf, fileName, lineNo, LOG_LEVEL_ARRAY[level], msg);
                    fflush(stdout);
                }
                return true;
            }
            static bool LoggingF(uint level, const char* fileName, int lineNo, const string& fmt, ...)
            {
                int size = 256;
                string msg;
                va_list ap;
                while (1) {
                    msg.resize(size);
                    va_start(ap, fmt);
                    int n = vsnprintf((char *)msg.c_str(), size, fmt.c_str(), ap);
                    va_end(ap);
                    if (n > -1 && n < size) {
                        msg.resize(n);
                        break;
                    }
                    if (n > -1)
                      size = n + 1;
                    else
                      size *= 2;
                }
                return Logging(level, msg, fileName, lineNo);
            }
    };
}

#endif
