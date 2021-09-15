//
// Created by xmmmmmovo on 2021/9/15.
//
#include "tcp.hpp"
#include "logger.hpp"
#include "socket.hpp"
#include "utils.hpp"

namespace server::net {

tcp_server_shared_ptr TcpServer::start_server(const std::string &host,
                                              unsigned short     port,
                                              bool               reuse_port) {
    tcp_server_shared_ptr ptr(new TcpServer());
    int                   rc = ptr->bind_listen(host, port, reuse_port);
    if (rc != OK) {
        LOG(ERROR, "bind_listen to %s:%d failed %d %s", host.c_str(), port,
            errno, strerror(errno));
        return nullptr;
    }
    return ptr;
}

int TcpServer::bind_listen(const std::string &host, unsigned short port,
                           bool reuse_port) {
    int rc = OK;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    rc     = set_reuse_address(fd);
    RC_CHECK(rc, ERROR, "set socket reuse option failed");
    rc = set_reuse_port(fd);
    RC_CHECK(rc, ERROR, "set socket reuse option failed");
    rc = utils::add_fd_flag(fd, FD_CLOEXEC);
    RC_CHECK(rc, ERROR, "add fd flag FD_CLOEXEC failed");
    rc = ::bind(fd, host.c_str(), port, reuse_port);
done:
    return rc;
error:
    close(fd);
    goto done;
}
}// namespace server::net