//
// Created by xmmmmmovo on 2021/9/15.
//

#ifndef SERVER_SOCKET_HPP
#define SERVER_SOCKET_HPP

#include "core.hpp"

namespace server::net {
int set_reuse_address(int fd, bool val = true);

int set_reuse_port(int fd, int val = true);
}// namespace server::net

#endif//SERVER_SOCKET_HPP
