/**
 * @file main.cpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2021-08-29
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "core.hpp"
#include "db.hpp"
#include "logger.hpp"
#include "server.hpp"

namespace server {

core::server_shared_ptr server = nullptr;

void bootsrap() {
    int rc = OK;
    rc     = db::initdb("../store/database.sqlite3");
    RC_CHECK(rc, ERROR, "数据库初始化错误！");
    server = core::AsyncServer::startServer("127.0.0.1", 12345);
    if (server == nullptr) {
        LOG(ERROR, "服务器初始化错误！");
        goto error;
    }
    return;
error:
    exit(rc);
}

void shutdown(int sig) {
    if (sig == SIGINT) { LOG(INFO, "收到信号！正在关闭服务器......"); }
}
}// namespace server

/**
 * @brief 主函数
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[]) {
    server::set_cur_level(server::DEBUG);
    server::bootsrap();
    signal(SIGINT, server::shutdown);

    return 0;
}