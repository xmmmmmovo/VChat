//
// Created by xmmmmmovo on 2021/9/10.
//

#ifndef SERVER_TCP_HPP
#define SERVER_TCP_HPP

#include "core.hpp"
#include "socket.hpp"

namespace server::net {
class TCPSocket : public Socket, private core::noncopyable {

};
}// namespace server::net

#endif//SERVER_TCP_HPP
