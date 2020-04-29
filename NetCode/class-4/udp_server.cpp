//
// Created by xmmmmmovo on 2020/4/29.
//
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

constexpr int BUF_SIZE = 1024;

void error_handler(char *message);

int main(int argc, char *argv[]) {
    int serv_sock;
    char message[BUF_SIZE];
    sockaddr_in serv_addr{}, clnt_addr{};
    socklen_t clnt_addr_size;

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serv_sock == -1) {
        error_handler("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    

    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}