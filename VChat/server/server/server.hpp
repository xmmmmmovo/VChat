//
// Created by xmmmmmovo on 2021/9/11.
//

#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include "core.hpp"
#include "tcp.hpp"
#include "thread.hpp"

namespace server::core {
class AsyncServer;

using server_shared_ptr = std::shared_ptr<AsyncServer>;

class AsyncServer : private noncopyable {
public:
    static server_shared_ptr start_server(const std::string &host,
                                         unsigned short     port);
    AsyncServer() = default;
    void exit() {
        //        threadPool_.exit();
        //        threadPool_.join();
    }
    net::tcp_server_shared_ptr _tcp_server;
    ThreadPool                 _thread_pool;
};
}// namespace server::core

#endif//SERVER_SERVER_HPP
