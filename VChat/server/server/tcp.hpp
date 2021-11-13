//
// Created by xmmmmmovo on 2021/9/15.
//

#ifndef SERVER_TCP_HPP
#define SERVER_TCP_HPP

#include "core.hpp"

namespace server::net {

/**
 * @brief 添加fd flag
 * 
 * @param fd 
 * @param flag 
 * @return int 
 */
int add_fd_flag(int fd, int flag) {
    int ret = fcntl(fd, F_GETFD);
    return fcntl(fd, F_SETFD, ret | flag);
}

class TcpServer;

using tcp_server_shared_ptr = std::shared_ptr<TcpServer>;

class TcpServer : private core::noncopyable {
public:
    static tcp_server_shared_ptr start_server(const std::string &host,
                                              unsigned short     port,
                                              bool reuse_port = false);
    int bind_listen(const std::string &host, unsigned short port,
                    bool reuse_port = false);

private:
    int         _fd;
    sockaddr_in _addr;
    int         _addr_len;

    void handle_accept();
};
}// namespace server::net

#endif//SERVER_TCP_HPP
