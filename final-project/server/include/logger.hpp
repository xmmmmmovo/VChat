/**
 * @file logger.hpp
 * @author xmmmmmovo (lolicoin@foxmail.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "core.hpp"
#include <string>
#define LOG_STRINGMAX 4096

#define LOG(level, fmt, ...)                                                   \
    do {                                                                       \
        if (_curPDLevel >= level) {                                            \
            log(level, __func__, __FILE__, __LINE__, fmt, ##__VA_ARGS__);      \
        }                                                                      \
    } while (0)

#define CHECK(cond, retCode, gotoLabel, level, fmt, ...)                       \
    do {                                                                       \
        if (!(cond)) {                                                         \
            rc = (retCode);                                                    \
            LOG((level), fmt, ##__VA_ARGS__);                                  \
            goto gotoLabel;                                                    \
        }                                                                      \
    } while (0)

#define RC_CHECK(rc, level, fmt, ...)                                          \
    do {                                                                       \
        CHECK((EDB_OK == (rc)), (rc), error, (level), fmt, ##__VA_ARGS__);     \
    } while (0)


enum LEVEL { SEVERE = 0, ERROR, EVENT, WARNING, INFO, DEBUG };

extern LEVEL _curPDLevel;
const char * getPDLevelDesp(LEVEL level);

#define DFT_DIAGLEVEL WARNING
void log(LEVEL level, const char *func, const char *file, unsigned int line,
         const char *format, ...);
void log(LEVEL level, const char *func, const char *file, unsigned int line,
         std::string message);

#endif// LOGGER_HPP