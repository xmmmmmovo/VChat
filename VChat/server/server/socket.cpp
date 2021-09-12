/**
 * @file socket.cpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-29
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "socket.hpp"
#include "logger.hpp"
namespace server::net {


Socket::Socket() {
    _init    = false;
    _fd      = 0;
    _timeout = 0;
    initaddress();
}

Socket::Socket(unsigned int port, int timeout) : Socket() {
    _timeout                      = timeout;
    _sock_address.sin_family      = AF_INET;
    _sock_address.sin_addr.s_addr = htonl(INADDR_ANY);
    _sock_address.sin_port        = htons(port);
}

Socket::Socket(const char *pHostname, unsigned int port, int timeout)
    : Socket(port, timeout) {
    struct hostent *hp;
    if ((hp = gethostbyname(pHostname)))
        _sock_address.sin_addr.s_addr = *((int *) hp->h_addr_list[0]);
    else
        _sock_address.sin_addr.s_addr = inet_addr(pHostname);
}

Socket::Socket(const int *sock, int timeout) {
    int rc   = OK;
    _fd      = *sock;
    _init    = true;
    _timeout = timeout;
    initaddress();
    rc = getsockname(_fd, (sockaddr *) &_sock_address, &_address_len);
    if (rc) {
        LOG(ERROR, "Failed to get sock name, error = %d", SOCKET_GETLASTERROR);
        _init = false;
    } else {
        rc = getpeername(_fd, (sockaddr *) &_peer_address, &_peer_address_len);
        RC_CHECK(rc, ERROR, "Failed to get peer name, error = %d",
                 SOCKET_GETLASTERROR);
    }
done:
    return;
error:
    goto done;
}

int Socket::setSocketLi(int lOnOff, int linger) const {
    int           rc = OK;
    struct linger _linger {
        .l_onoff = lOnOff, .l_linger = linger
    };
    rc = setsockopt(_fd, SOL_SOCKET, SO_LINGER, (const void *) &_linger,
                    sizeof _linger);
    return rc;
}

void Socket::setAddress(const char *pHostname, unsigned int port) {
    hostent *hp;
    initaddress();
    _peer_address.sin_family = AF_INET;
    if ((hp = gethostbyname(pHostname))) {
        _sock_address.sin_addr.s_addr = *((int *) hp->h_addr_list[0]);
    } else {
        _sock_address.sin_addr.s_addr = inet_addr(pHostname);
    }
    _sock_address.sin_port = htons(port);
    _address_len           = sizeof _sock_address;
}

void Socket::close() {
    if (_init) {
        int i = 0;
        i     = ::close(_fd);
        if (i < 0) {
            LOG(ERROR, "关闭错误！");
            i = -1;
        }
        _init = false;
    }
}

void Socket::initaddress() {
    memset(&_sock_address, 0, sizeof(sockaddr_in));
    memset(&_peer_address, 0, sizeof(sockaddr_in));
    _peer_address_len = sizeof(_peer_address);
    _address_len      = sizeof(_sock_address);
}
}// namespace server::net