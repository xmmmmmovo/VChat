/**
 * @file logger.cpp
 * @author xmmmmmovo (lolicoin@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "logger.hpp"

const static char *PDLEVELSTRING[] = {"SEVERE",  "ERROR", "EVENT",
                                      "WARNING", "INFO",  "DEBUG"};

const char *getPDLevelDesp(LEVEL level) {
    if ((unsigned int) level > (unsigned int) DEBUG) { return "Unknow Level"; }
    return PDLEVELSTRING[(unsigned int) level];
}

const static char *LOG_STR_FORMAT =
        "%04d-%02d-%02d-%02d.%02d.%02d.%06d\
               \
Level:%s" OSS_NEWLINE "PID:%-37d" OSS_NEWLINE
        "Function:%-32sLine:%d" OSS_NEWLINE "File:%s" OSS_NEWLINE
        "Message:" OSS_NEWLINE "%s" OSS_NEWLINE OSS_NEWLINE;

LEVEL _curPDLevel = DFT_DIAGLEVEL;

void log(LEVEL level, const char *func, const char *file, unsigned int line,
         const char *format, ...) {
    int             rc = OK;
    va_list         ap;
    char            userInfo[LOG_STRINGMAX];// for user defined message
    char            sysInfo[LOG_STRINGMAX]; // for log header
    struct tm       otm;
    struct timeval  tv;
    struct timezone tz;
    time_t          tt;

    gettimeofday(&tv, &tz);
    tt = tv.tv_sec;
    localtime_r(&tt, &otm);

    // create user information
    va_start(ap, format);
    vsnprintf(userInfo, LOG_STRINGMAX, format, ap);
    va_end(ap);

    snprintf(sysInfo, LOG_STRINGMAX, LOG_STR_FORMAT, otm.tm_year + 1900,
             otm.tm_mon + 1, otm.tm_mday, otm.tm_hour, otm.tm_min, otm.tm_sec,
             tv.tv_usec, PDLEVELSTRING[level], getpid(), func, line, file,
             userInfo);
    printf("%s" OSS_NEWLINE, sysInfo);
    return;
}
