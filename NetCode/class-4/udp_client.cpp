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
constexpr int size_len = 4;

void error_handler(char *message);

int main(int argc, char *argv[]) {
    int sock;
    sockaddr_in serv_addr{}, from_addr{};
    int str_len = 0;
    char message[BUF_SIZE];

    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handler("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // 这里会自动将ip字符串转换为uint32_t类型IP数字
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    while (true) {
        fputs("Insert message(q to quit): ", stdout);
        fgets(message, sizeof(message), stdin);
        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }

        sendto(sock, message, strlen(message), 0,
               (sockaddr *) &serv_addr, sizeof(serv_addr));
        socklen_t adr_sz = sizeof(from_addr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0,
                           (sockaddr *) &from_addr, &adr_sz);
        message[str_len] = 0;
        printf("Message from server : %s", message);
    }

    close(sock);
    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}