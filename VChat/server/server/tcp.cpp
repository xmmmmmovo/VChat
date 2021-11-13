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
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct hostent *hp;
    memset(&_addr, 0, sizeof _addr);
    _addr.sin_family = AF_INET;
    if ((hp = gethostbyname(host.c_str()))) {
        _addr.sin_addr.s_addr = *((int *) hp->h_addr_list[0]);
    } else {
        _addr.sin_addr.s_addr = inet_addr(host.c_str());
    }
    _addr.sin_port = htons(port);
    _addr_len      = sizeof _addr;
    delete hp;

    rc = set_reuse_address(fd);
    RC_CHECK(rc, ERROR, "set socket reuse option failed");
    rc = set_reuse_port(fd);
    RC_CHECK(rc, ERROR, "set socket reuse option failed");
    rc = add_fd_flag(fd, FD_CLOEXEC);
    RC_CHECK(rc, ERROR, "add fd flag FD_CLOEXEC failed");
    rc = ::bind(fd, (sockaddr *) &_addr, _addr_len);
    RC_CHECK(NETWORK, ERROR, "Failed to bind socket");
    rc = listen(_fd, SOMAXCONN);
    RC_CHECK(NETWORK, ERROR, "Failed to listen socket");
done:
    return rc;
error:
    close(fd);
    goto done;
}
}// namespace server::net