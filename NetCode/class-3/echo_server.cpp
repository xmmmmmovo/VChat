//
// Created by xmmmmmovo on 2020/4/16.
//
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using std::stoi;
using std::string;
using std::to_string;

constexpr int BUF_SIZE = 1024;

void error_handler(char *message);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int size_len = 4;
    char size_buf[size_len];
    sockaddr_in serv_addr{}, clnt_addr{};
    socklen_t clnt_addr_size;
    int str_len = 0;

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handler("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));// 初始化内存

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);// 当前主机ip
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handler("bind() error");
    }

    if (listen(serv_sock, 5) == -1) {
        error_handler("listen() error");
    }

    clnt_addr_size = sizeof(clnt_addr);// 算长度

    ///主体
    for (int i = 0; i < 5; ++i) {
        clnt_sock = accept(serv_sock, (sockaddr *) &clnt_addr, &clnt_addr_size);
        if (clnt_sock == 1) {
            error_handler("accept() error!");
        } else {
            printf("Connected client %d \n", i + 1);
        }


        while (true) {
            if ((str_len = read(clnt_sock, message, size_len)) != 0) {
                if ((str_len = read(clnt_sock, &message[str_len], stoi(message))) != 0) {
                    write(clnt_sock, message, str_len + size_len);
                } else {
                    break;
                }
            } else {
                break;
            }
        }

        close(clnt_sock);
    }
    ///

    close(serv_sock);
    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}