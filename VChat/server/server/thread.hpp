/**
 * @file thread.hpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef THREAD_HPP
#define THREAD_HPP
#include "core.hpp"

namespace server {
namespace sync {
    template<typename T>
    class Queue : private core::noncopyable {};
}// namespace sync

namespace core {
    using namespace std;
    class ThreadPool : private noncopyable {
    public:
        ThreadPool();
        ~ThreadPool();
        void start();

    private:
        sync::Queue<int> _tasks;
        vector<thread>   _threads;
    };
}// namespace core
}// namespace server

#endif// THREAD_HPP