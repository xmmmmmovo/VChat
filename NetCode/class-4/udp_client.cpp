//
// Created by xmmmmmovo on 2020/4/29.
//
#include <arpa/inet.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

constexpr int BUF_SIZE = 1024;
constexpr int size_len = 4;
constexpr int edge     = 10;

using std::string;
using std::to_string;

void error_handler(char *message);

int main(int argc, char *argv[]) {
    int         sock;
    sockaddr_in serv_addr{}, from_addr{};
    int         str_len = 0;
    char        message[ BUF_SIZE ];

    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[ 0 ]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handler("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // 这里会自动将ip字符串转换为uint32_t类型IP数字
    serv_addr.sin_addr.s_addr = inet_addr(argv[ 1 ]);
    serv_addr.sin_port        = htons(atoi(argv[ 2 ]));

    /// 主体
    while (true) {
        fputs("Insert message(q to quit): ", stdout);
        fgets(message + 3, sizeof(message) - 3, stdin);
        if (!strcmp(message + 3, "q\n") || !strcmp(message + 3, "Q\n")) {
            break;
        }
        /// 发的时候就需要规定协议发送
        int tl = strlen(message + 3);
        if (tl < edge) {
            tl += 2;
            message[ 1 ] = '1';
            message[ 2 ] = tl;
            // 短数据发送
            sendto(sock, message + 1, tl, 0,
                   (sockaddr *) &serv_addr, sizeof(serv_addr));
        } else {
            int times    = ceil(tl * 1.0 / edge);
            message[ 0 ] = '0';
            message[ 1 ] = (char) times;
            sendto(sock, message, 2, 0,
                   (sockaddr *) &serv_addr, sizeof(serv_addr));

            for (int i = 0; i < times; ++i) {
                int st            = i * edge;
                message[ st ]     = '2';
                message[ st + 1 ] = (char) (i + 1);
                int n             = tl + 3 - st > edge ? edge : tl + 3 - st;
                message[ st + 2 ] = n;
                sendto(sock, &message[ st ], n, 0,
                       (sockaddr *) &serv_addr, sizeof(serv_addr));
            }
        }

        socklen_t adr_sz = sizeof(from_addr);
        char      buf[ 3 ];
        str_len = recvfrom(sock, buf, 2, 0,
                           (sockaddr *) &from_addr, &adr_sz);
        if (buf[ 0 ] == '1') {
            str_len = recvfrom(sock, message, (int) buf[ 1 ], 0,
                               (sockaddr *) &from_addr, &adr_sz);
        } else if (buf[ 0 ] == '0') {
            int n   = (int) buf[ 1 ];
            int idx = 0;
            for (int i = 0; i < n; ++i) {
                str_len = recvfrom(sock, buf, 3, 0,
                                   (sockaddr *) &from_addr, &adr_sz);
                str_len = recvfrom(sock, &message[ idx ], (int) buf[ 2 ], 0,
                                   (sockaddr *) &from_addr, &adr_sz);
                idx += str_len;
            }
        } else if (buf[ 0 ] == '2') {
            str_len = recvfrom(sock, &buf[ 2 ], 1, 0,
                               (sockaddr *) &from_addr, &adr_sz);
            {
                char tp[ (int) buf[ 2 ] ];
                str_len = recvfrom(sock, tp, (int) buf[ 2 ], 0,
                                   (sockaddr *) &from_addr, &adr_sz);
            }
        }
        message[ str_len ] = 0;
        printf("Message from server : %s\n", message);
    }
    ///
    close(sock);
    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}