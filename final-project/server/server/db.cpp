/**
 * @file db.cpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "db.hpp"
#include "core.hpp"
#include "logger.hpp"
#include <sqlite3.h>

namespace server {
static sqlite3 *sql = nullptr;

int initdb(const char *filepath) {
    int ret = sqlite3_open_v2(filepath, &sql,
                              SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |
                                      SQLITE_OPEN_NOMUTEX |
                                      SQLITE_OPEN_SHAREDCACHE,
                              nullptr);
    if (ret == SQLITE_OK) {
        LOG(INFO, "初始化数据库成功！");
        return OK;
    } else {
        LOG(ERROR, "无法连接到sqlite，初始化失败！");
        return IO;
    }
    return 0;
}
}