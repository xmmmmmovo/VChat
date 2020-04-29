//
// Created by xmmmmmovo on 2020/4/16.
//
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using std::stoi;
using std::string;
using std::to_string;

constexpr int BUF_SIZE = 1024;

void error_handler(char *messgae);

int main(int argc, char *argv[]) {
    int sock;
    sockaddr_in serv_addr{};
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

    if (connect(sock, (sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handler("connect() error!");
    } else {
        puts("Connected......");
    }

    while (true) {
        fputs("Input message(Q/q to quit): ", stdout);
        std::fgets(message, BUF_SIZE, stdin);

        if (!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }

        int l = strlen(message);
        printf("len = %d\n", l);
        string s = to_string(l);
        s.resize(4);
        write(sock, s.c_str(), 4);
        write(sock, message, strlen(message));
        char buf[4];
        str_len = read(sock, buf, 4);
        str_len = read(sock, message, stoi(buf));
        message[str_len] = 0;
        printf("Message from server: %s\n", message);
    }


    close(sock);
    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}