/**
 * @file utils.cpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "utils.hpp"

namespace server {
namespace utils {
    using namespace std;
    int64_t time_micro() {
        chrono::time_point<chrono::system_clock> p =
                chrono::system_clock::now();
        return chrono::duration_cast<chrono::microseconds>(p.time_since_epoch())
                .count();
    }
    int64_t time_milli() { return time_micro() / 1000; }

    int64_t steady_micro() {
        chrono::time_point<chrono::steady_clock> p =
                chrono::steady_clock::now();
        return chrono::duration_cast<chrono::microseconds>(p.time_since_epoch())
                .count();
    }
    int64_t steady_milli() { return steady_micro() / 1000; }

    std::string readable_time(time_t t) {
        auto               tt  = std::time(nullptr);
        auto               tm = *std::localtime(&tt);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
        return oss.str();
    }

    int64_t atoi(const char *b, const char *e) {
        return strtol(b, (char **) &e, 10);
    }

    int64_t atoi2(const char *b, const char *e) {
        char ** ne = (char **) &e;
        int64_t v  = strtol(b, ne, 10);
        return ne == (char **) &e ? v : -1;
    }
    int64_t atoi(const char *b) { return atoi(b, b + strlen(b)); }
    
    int     add_fd_flag(int fd, int flag) {
        int ret = fcntl(fd, F_GETFD);
        return fcntl(fd, F_SETFD, ret | flag);
    }

}// namespace utils
}// namespace server
