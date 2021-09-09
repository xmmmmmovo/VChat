/**
 * @file utils.hpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef SERVER_UTILS_HPP
#define SERVER_UTILS_HPP

#include <chrono>
#include <fcntl.h>
#include <memory>
#include <stdarg.h>

namespace server {
namespace utils {
    int64_t time_micro();
    int64_t time_milli();

    int64_t     steady_micro();
    int64_t     steady_milli();
    std::string readable_time(time_t t);
    int64_t     atoi(const char *b, const char *e);
    int64_t     atoi2(const char *b, const char *e);
    int64_t     atoi(const char *b);
    int         add_fd_flag(int fd, int flag);
}// namespace utils
}// namespace server

#endif//SERVER_UTILS_HPP
