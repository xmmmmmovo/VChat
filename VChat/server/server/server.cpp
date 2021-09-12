//
// Created by xmmmmmovo on 2021/9/11.
//

#include "server.hpp"

namespace server::core {
AsyncServer::server_shared_ptr AsyncServer::startServer(const string  &host,
                                                        unsigned short port) {
    server_shared_ptr server_ptr = server_shared_ptr(new AsyncServer());
    //    server_ptr->_server          = tcp_shared_ptr(new net::TCPSocket());
    return server_ptr->_server ? server_ptr : nullptr;
}
}// namespace server::core