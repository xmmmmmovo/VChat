//
// Created by xmmmmmovo on 2021/9/15.
//

#ifndef SERVER_TCP_HPP
#define SERVER_TCP_HPP

#include "core.hpp"

namespace server::net {
class TcpServer;

using tcp_server_shared_ptr = std::shared_ptr<TcpServer>;

class TcpServer : private core::noncopyable {
public:
    static tcp_server_shared_ptr start_server(const std::string &host, unsigned short port, bool reuse_port = false);
    int bind_listen(const std::string &host, unsigned short port, bool reuse_port = false);
private:
    int _fd;
};
}// namespace server::net

#endif//SERVER_TCP_HPP
