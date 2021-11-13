//
// Created by xmmmmmovo on 2021/9/11.
//

#ifndef SERVER_POLLER_HPP
#define SERVER_POLLER_HPP

#include "core.hpp"

namespace server::io {
class IPoller : private core::noncopyable {
    int64_t _id;
    int     last_active_poll;
};
}// namespace server::io

#endif//SERVER_POLLER_HPP
