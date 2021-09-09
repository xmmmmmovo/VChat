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

namespace server {

void bootsrap() {
    int rc = OK;
    if ((rc = initdb("../store/database.sqlite3")) != OK) goto err;
err:
    exit(rc);
}

void shutdown(int sig) {
    if (sig == SIGINT) {}
    return;
}
}// namespace server


int main(int argc, char *argv[]) {
    server::set_cur_level(server::DEBUG);
    server::bootsrap();
    signal(SIGINT, server::shutdown);

    return 0;
}