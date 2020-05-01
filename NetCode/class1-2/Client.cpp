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

void error_handler(char *messgae);

int main(int argc, char *argv[]) {
    int         sock;
    sockaddr_in serv_addr{};
    int         str_len = 0;
    int         idx = 0, read_len = 0;
    string      message;// 信息流
    message.resize(100, '\0');

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

    if (connect(sock, (sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handler("connect() error!");
    }
    bool check = false;

    // 每次只读出一个字节
    while (read_len = read(sock, &message[ idx++ ], 1)) {
        if (str_len == -1) {
            if (check)
                error_handler("read() error!");
            else
                sleep(3);
        }

        str_len += read_len;
    }

    printf("Message from server is : %s \n", message.c_str());
    printf("Function read call count : %d \n", str_len);
    close(sock);
    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}