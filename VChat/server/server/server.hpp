//
// Created by xmmmmmovo on 2021/9/11.
//

#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include "core.hpp"

namespace server::core {
class AsyncServer : private noncopyable {
    using server_shared_ptr = std::shared_ptr<AsyncServer>;
    static server_shared_ptr startServer(const std::string &host,
                                         unsigned short     port);
    AsyncServer() {}
    void exit() {
        threadPool_.exit();
        threadPool_.join();
    }
    server_shared_ptr _server;
    ThreadPool        _thread_pool;
};
}// namespace server::core

#endif//SERVER_SERVER_HPP
