/**
 * @file file.cpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "file.hpp"

namespace server {
namespace io {
    using namespace std;
    tuple<int, string &&> get_content(const string &filename) {
        string content;
        int    fd = open(filename.c_str(), O_RDONLY);
        if (fd < 0) { return make_tuple(IO, nullptr); }
        core::defer d1([=] { close(fd); });
        char        buf[4096];
        while (1) {
            int r = read(fd, buf, sizeof buf);
            if (r < 0) {
                return make_tuple(IO, content);
            } else if (r == 0) {
                break;
            }
            content.append(buf, r);
        }
        return make_tuple(OK, content);
    }

    bool fileisExists(const string &filename) {
        return access(filename.c_str(), F_OK) == 0;
    }
    
}// namespace io
}// namespace server