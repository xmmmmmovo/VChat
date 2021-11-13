//
// Created by xmmmmmovo on 2021/9/15.
//

#ifndef SERVER_CODEC_HPP
#define SERVER_CODEC_HPP

#include "core.hpp"

namespace server::net {
struct Response {
    std::size_t length;
};

Response *response_wrapper() {}

}// namespace server::net

#endif//SERVER_CODEC_HPP
