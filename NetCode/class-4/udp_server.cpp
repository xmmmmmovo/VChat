//
// Created by xmmmmmovo on 2020/4/29.
//
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

constexpr int BUF_SIZE = 256;
//constexpr int BUF_SIZE = 10;

void error_handler(char *message);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <port> \n", argv[ 0 ]);
        exit(1);
    }

    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    sockaddr_in sockAddr{};
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family      = AF_INET;
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddr.sin_port        = htons(atoi(argv[ 1 ]));

    if (-1 == bind(sock, (struct sockaddr *) &sockAddr, sizeof(sockAddr))) {
        error_handler("bind() error!");
    }

    sockaddr_in clntAddr{};
    socklen_t   clntAddrLen = sizeof(clntAddr);

    char buf[ 512 ];
    while (true) {
        int recv_len = recvfrom(sock, buf, BUF_SIZE, 0, (struct sockaddr *) &clntAddr, &clntAddrLen);
        printf("recv len = %d\n", recv_len);
        sendto(sock, buf, recv_len, 0, (struct sockaddr *) &clntAddr, sizeof(clntAddr));
    }

    close(sock);
    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}