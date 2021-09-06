/**
 * @file core.hpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef CORE_HPP
#define CORE_HPP

#include <arpa/inet.h>
#include <cerrno>
#include <csignal>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fcntl.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/syslimits.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace server {
namespace core {

#define OSS_MAX_PATHSIZE PATH_MAX
#define OSS_FILE_SEP_STR "/"
#define OSS_FILE_SEP_CHAR *((const char *) OSS_FILE_SEP_STR)[0]
#define OSS_NEWLINE "\n"
// error code list
#define OK 0
#define IO -1
#define INVALIDARG -2
#define PERM -3
#define OOM -4
#define SYS -5
#define PMD_HELP_ONLY -6
#define PMD_FORCE_SYSTEM_EDU -7
#define TIMEOUT -8
#define QUIESCED -9
#define NETWORK -11
#define NETWORK_CLOSE -12
#define APP_FORCED -13
#define IXM_ID_EXIST -14
#define HEADER_INVALID -15
#define IXM_ID_NOT_EXIST -16
#define NO_ID -17

}// namespace core
}// namespace server

#endif// CORE_HPP