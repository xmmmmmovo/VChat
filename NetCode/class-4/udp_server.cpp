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
    int         serv_sock;
    char        message[ BUF_SIZE ];
    sockaddr_in serv_addr{}, clnt_addr{};
    socklen_t   clnt_addr_size;
    int         str_len = 0;

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[ 0 ]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serv_sock == -1) {
        error_handler("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family      = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);// 当前主机ip
    serv_addr.sin_port        = htons(atoi(argv[ 1 ]));

    if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handler("bind() error");
    }

    while (true) {
        clnt_addr_size = sizeof(clnt_addr);
        str_len        = recvfrom(serv_sock, message, 2, 0,
                           (sockaddr *) &clnt_addr, &clnt_addr_size);
        if (message[ 0 ] == '1') {
            str_len = recvfrom(serv_sock, message + 2, (int) message[ 2 ], 0,
                               (sockaddr *) &clnt_addr, &clnt_addr_size);
            sendto(serv_sock, message, str_len + 2, 0,
                   (sockaddr *) &clnt_addr, clnt_addr_size);
            message[ str_len + 2 ] = 0;
        } else if (message[ 0 ] == '0') {
            sendto(serv_sock, message, 2, 0,
                   (sockaddr *) &clnt_addr, clnt_addr_size);
            int n   = (int) message[ 1 ];
            int idx = 0;
            for (int i = 0; i < n; ++i) {
                str_len = recvfrom(serv_sock, message, 3, 0,
                                   (sockaddr *) &clnt_addr, &clnt_addr_size);
                str_len = recvfrom(serv_sock, &message[ idx ], (int) message[ 2 ], 0,
                                   (sockaddr *) &clnt_addr, &clnt_addr_size);
                idx += str_len;
            }
        } else if (message[ 0 ] == '2') {
            str_len = recvfrom(serv_sock, &message[ 2 ], 1, 0,
                               (sockaddr *) &clnt_addr, &clnt_addr_size);
            {
                char tp[ (int) message[ 2 ] ];
                str_len = recvfrom(serv_sock, tp, (int) message[ 2 ], 0,
                                   (sockaddr *) &clnt_addr, &clnt_addr_size);
            }
        }
    }

    close(serv_sock);
    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}