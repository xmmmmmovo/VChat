//
// Created by xmmmmmovo on 2020/4/29.
//
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <Windows.h>

int main() {
    WORD ver = MAKEWORD(2, 2);
    WSADATA wsadata;
    WSAStartup(ver, &wsadata);
    ///
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9000);
    sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    bind(sock, (sockaddr *) &sin, sizeof(sin));
    ///
    WSACleanup();
    return 0;
}