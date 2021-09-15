//
// Created by xmmmmmovo on 2021/9/11.
//

#include "server.hpp"

namespace server::core {
server_shared_ptr AsyncServer::start_server(const string  &host,
                                            unsigned short port) {
    server_shared_ptr server_ptr = server_shared_ptr(new AsyncServer());
    server_ptr->_tcp_server      = net::TcpServer::start_server(host, port);
    return server_ptr->_tcp_server ? server_ptr : nullptr;
}
}// namespace server::core