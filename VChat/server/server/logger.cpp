/**
 * @file logger.cpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "logger.hpp"

namespace server {
const static char *PDLEVELSTRING[] = {"SEVERE",  "ERROR", "EVENT",
                                      "WARNING", "INFO",  "DEBUG"};

const char *get_PD_level_desp(LEVEL level) {
    if ((unsigned int) level > (unsigned int) DEBUG) { return "Unknow Level"; }
    return PDLEVELSTRING[(unsigned int) level];
}

const static char *LOG_STR_FORMAT =
        "%04d-%02d-%02d-%02d.%02d.%02d.%06d"
        "\tLevel:%s\t"
        "Function:%-8sLine:%d" OSS_NEWLINE "File:%s" OSS_NEWLINE
        "Message: %s" OSS_NEWLINE;

LEVEL _curPDLevel = DFT_DIAGLEVEL;

void set_cur_level(LEVEL level) { _curPDLevel = level; }

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
             tv.tv_usec, PDLEVELSTRING[level], func, line, file, userInfo);
    printf("%s" OSS_NEWLINE, sysInfo);
    return;
}
}// namespace server