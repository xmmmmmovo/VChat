/**
 * @file socket.hpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "core.hpp"

#define SOCKET_GETLASTERROR errno

// by default 10ms timeout
#define OSS_SOCKET_DFT_TIMEOUT 10000

// max hostname
#define OSS_MAX_HOSTNAME NI_MAXHOST
#define OSS_MAX_SERVICENAME NI_MAXSERV

namespace server::net {
using rescode = int;

int get_host_name(char *pname, const int name_len) {
    return gethostname(pname, name_len);
}

std::tuple<rescode, unsigned short> get_port(const char *pname) {
    unsigned short port = 0;
    rescode        rc   = OK;
    servent       *servinfo_ptr;
    servinfo_ptr = getservbyname(pname, "tcp");
    if (!servinfo_ptr) {
        port = atoi(pname);
    } else {
        port = (unsigned short) ntohs(servinfo_ptr->s_port);
    }
    return std::make_tuple(rc, port);
}

}// namespace server::net
#endif// SOCKET_HPP
