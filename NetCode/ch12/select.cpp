/**
 * @file select.cpp
 * @author xmmmmmovo (13256172360@163.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>

#define BUF_SIZE 30

using namespace std;

int main(int argc, char const *argv[]) {
    fd_set  reads, temps;
    int     res, str_len;
    char    buf[ BUF_SIZE ];
    timeval timeout;

    FD_ZERO(&reads);
    FD_SET(0, &reads);// 0是标准输出

    /*
    timeout.tv_sec=5;
    timeout.tv_usec=5000;
    */
    while (1) {
        temps          = reads;
        timeout.tv_sec = 5, timeout.tv_usec = 0;
        res = select(1, &temps, 0, 0, &timeout);
        if (-1 == res) {
            puts("select() error!");
            break;
        } else if (0 == res) {
            puts("timeout!");
        } else {
            if (FD_ISSET(0, &temps)) {
                str_len        = read(0, buf, BUF_SIZE);
                buf[ str_len ] = 0;
                printf("message from console: %s", buf);
            }
        }
    }

    return 0;
}