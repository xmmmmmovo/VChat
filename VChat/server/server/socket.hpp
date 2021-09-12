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

int get_host_name(char *pname, const int name_len) {
    return gethostname(pname, name_len);
}

std::tuple<int, unsigned short> get_port(const char *pname) {
    unsigned short port = 0;
    int            rc   = OK;
    servent       *servinfo_ptr;
    servinfo_ptr = getservbyname(pname, "tcp");
    if (!servinfo_ptr) {
        port = atoi(pname);
    } else {
        port = (unsigned short) ntohs(servinfo_ptr->s_port);
    }
    return std::make_tuple(rc, port);
}

class Socket {
protected:
    int         _fd;
    socklen_t   _address_len;
    socklen_t   _peer_address_len;
    sockaddr_in _sock_address;
    sockaddr_in _peer_address;
    bool        _init;
    int         _timeout;

    unsigned int _get_port(sockaddr_in *addr);
    int  _get_address(sockaddr_in *addr, char *pAddress, unsigned int length);
    void initaddress();

public:
    int  setSocketLi(int lOnOff, int linger) const;
    void setAddress(const char *pHostname, unsigned int port);
    // create a listening socket
    Socket();
    explicit Socket(unsigned int port, int timeout = 0);
    // create a connection socket
    Socket(const char *pHostname, unsigned int port, int timeout = 0);
    // create from a existing socket
    explicit Socket(const int *sock, int timeout = 0);
    ~Socket() { close(); }
    virtual int init_socket() = 0;
    int         bind_listen();
    bool        is_connected();
    int  send(const char *pMsg, int len, int timeout = OSS_SOCKET_DFT_TIMEOUT,
              int flags = 0);
    int  recv(char *pMsg, int len, int timeout = OSS_SOCKET_DFT_TIMEOUT,
              int flags = 0);
    int  recvNF(char *pMsg, int len, int timeout = OSS_SOCKET_DFT_TIMEOUT);
    int  connect();
    void close();
    int  accept(int *sock, struct sockaddr *addr, socklen_t *addrlen,
                int timeout = OSS_SOCKET_DFT_TIMEOUT);
    int  disableNagle();
    unsigned int getPeerPort();
    int          getPeerAddress(char *pAddress, unsigned int length);
    unsigned int getLocalPort();
    int          getLocalAddress(char *pAddress, unsigned int length);
    int          setTimeout(int seconds);
};
}// namespace server::net
#endif// SOCKET_HPP
