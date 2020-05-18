//
// Created by xmmmmmovo on 2020/4/29.
//
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

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
    struct sockaddr_in addr_{};
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

    char buf[ 256 ];
    while (true) {
        fgets(buf, sizeof(buf), stdin);
        int sendLen = sock.sendto(addr, buf, sizeof(buf));
        int recvLen = sock.recvfrom(addr, buf, sizeof(buf) - 1);
        printf("recvLen = %d\n", recvLen);

        buf[ recvLen ] = 0;
        printf("Message from server: %s", buf);
    }

    return 0;
}

void error_handler(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(0);
}