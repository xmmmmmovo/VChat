//
// Created by xmmmmmovo on 2021/9/10.
//
#include "tcp.hpp"
#include "logger.hpp"

namespace server::net {
int TCPSocket::init_socket() {
    int rc = OK;
    if (_init) { goto done; }
    initaddress();
    _fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1 == _fd) { RC_CHECK(NETWORK, ERROR, "", SOCKET_GETLASTERROR); }
    _init = false;
    setTimeout(_timeout);
done:
    return rc;
error:
    goto done;
}
}// namespace server::net