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

namespace server {
namespace net {
#define SOCKET_GETLASTERROR errno

// by default 10ms timeout
#define OSS_SOCKET_DFT_TIMEOUT 10000

// max hostname
#define OSS_MAX_HOSTNAME NI_MAXHOST
#define OSS_MAX_SERVICENAME NI_MAXSERV

class Socket {
private:
    int         _fd;
    socklen_t   _addressLen;
    socklen_t   _peerAddressLen;
    sockaddr_in _sockAddress;
    sockaddr_in _peerAddress;
    bool        _init;
    int         _timeout;

protected:
    unsigned int _getPort(sockaddr_in *addr);
    int _getAddress(sockaddr_in *addr, char *pAddress, unsigned int length);

public:
    int  setSocketLi(int lOnOff, int linger);
    void setAddress(const char *pHostname, unsigned int port);
    // create a listening socket
    Socket();
    Socket(unsigned int port, int timeout = 0);
    // create a connection socket
    Socket(const char *pHostname, unsigned int port, int timeout = 0);
    // create from a existing socket
    Socket(int *sock, int timeout = 0);
    ~Socket() { close(); }
    int  initSocket();
    int  bind_listen();
    bool isConnected();
    int  send(const char *pMsg, int len,
                int timeout = OSS_SOCKET_DFT_TIMEOUT, int flags = 0);
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
    static int   getHostName(char *pName, int nameLen);
    static int   getPort(const char *pServiceName, unsigned short &port);
};
}// namespace net
}// namespace server
#endif// SOCKET_HPP
