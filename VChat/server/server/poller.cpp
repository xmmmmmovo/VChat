//
// Created by xmmmmmovo on 2021/9/11.
//

#include "poller.hpp"

#ifdef __linux__
#include <sys/epoll.h>
#elif __APPLE__
#include <sys/event.h>
#endif

namespace server::io {

#ifdef __linux__
class EpollPoller : public IPoller {};
#elif __APPLE__
class KqueuePoller : public IPoller {
    int _fd;
};
#endif
}// namespace server::io