//
// Created by xmmmmmovo on 2021/9/15.
//

#include "socket.hpp"

namespace server::net {

int set_reuse_address(int fd, bool val) {
    return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

int set_reuse_port(int fd, int val) {
#ifndef SO_REUSEPORT
    return OK;
#else
    return setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));
#endif
}

}// namespace server::net