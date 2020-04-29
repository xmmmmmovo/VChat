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

using std::string;
using std::to_string;

void error_handler(char *message);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;

    struct sockaddr_in serv_addr {};
    struct sockaddr_in clnt_addr {};
    socklen_t clnt_addr_size;

    string message = "Hello World!";

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

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1) {
        error_handler("accept() error");
    }

    for (int i = 1; i < 4; ++i) {
        sleep(rand() % 2);
        string tmp = message + to_string(i);
        write(clnt_sock, tmp.c_str(), tmp.size());
    }

    // write(clnt_sock, message.c_str(), message.size());// 连接之后直接向client写入数据
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}