//
// Created by xmmmmmovo on 2020/4/29.
//
#include <arpa/inet.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

constexpr int BUF_SIZE = 256;
//constexpr int BUF_SIZE = 10;

void error_handler(char *message);

class InetAddress {
public:
    explicit InetAddress(std::string port, const std::string ip = "") {
        memset(&addr_, 0, sizeof(addr_));
        addr_.sin_family = AF_INET;
        addr_.sin_port   = htons(atoi(port.c_str()));

        if (ip == "")
            addr_.sin_addr.s_addr = htonl(INADDR_ANY);
        else
            addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    }

    ~InetAddress() = default;

    sockaddr_in &getAddr() {
        return addr_;
    }

private:
    struct sockaddr_in addr_ {};
};

class Socket {
public:
    explicit Socket(int type) {
        fd_ = socket(PF_INET, type, 0);
    }
    ~Socket() {
        close(fd_);
    }

    ssize_t sendto(InetAddress &addr, void *pData, size_t nBytes) const {
        sockaddr *toAddr  = (sockaddr *) &(addr.getAddr());
        socklen_t addrLen = sizeof(addr.getAddr());

        return ::sendto(fd_, pData, nBytes, 0, toAddr, addrLen);
    }

    ssize_t recvfrom(InetAddress &addr, void *buf, size_t nBytes) const {
        return ::recvfrom(fd_, buf, nBytes, 0, 0, 0);
    }

private:
    int fd_;
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <ip> <port> \n", argv[ 0 ]);
        exit(1);
    }

    Socket sock(SOCK_DGRAM);

    InetAddress addr(argv[ 2 ], argv[ 1 ]);

    char buf[ 1024 ];
    int  sl = 0;
    while (true) {
        fgets(buf + 3, sizeof(buf) - 3, stdin);
        sl = strlen(buf + 3) - 1;
        printf("str len = %d\n", sl);
        if (sl < BUF_SIZE - 3) {
            buf[ 1 ]     = (char) 1;
            buf[ 2 ]     = (char) sl;
            int send_len = sock.sendto(addr, buf + 1, sl + 2);
            printf("send len = %d\n", send_len);
        } else {
            int pack_num = ceil((double) sl / (BUF_SIZE - 3));
            buf[ 0 ]     = (char) 0;
            buf[ 1 ]     = (char) pack_num;
            sock.sendto(addr, buf, 2);
            int st = 0;
            for (int i = 0; i < pack_num; ++i) {
                st            = i * (BUF_SIZE - 3);
                buf[ st ]     = (char) 2;
                buf[ st + 1 ] = (char) (i + 1);
                buf[ st + 2 ] = i == pack_num - 1 ? strlen(buf + st + 3) : BUF_SIZE - 3;
                sock.sendto(addr, buf + st, BUF_SIZE);
            }
        }


        int recv_len    = sock.recvfrom(addr, buf, BUF_SIZE);
        buf[ recv_len ] = 0;

        if (buf[ 0 ] == 1) {
            printf("Message from server: %s\n", buf + 2);
        } else if (buf[ 0 ] == 0) {
            // 数据包获取
            int  pack_num = (int) buf[ 1 ];
            int  cnt      = 0;
            char pc_buf[ BUF_SIZE ];
            for (int i = 0; i < pack_num; ++i) {
                recv_len = sock.recvfrom(addr, pc_buf, BUF_SIZE);
                std::copy(pc_buf + 3, pc_buf + recv_len, buf + cnt);
                cnt += (int) pc_buf[ 2 ];
            }
            printf("Message from server: %s\n", buf);
        }
    }

    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}