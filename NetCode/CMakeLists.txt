cmake_minimum_required(VERSION 3.10)
project(NetCode)

set(CMAKE_CXX_STANDARD 14)

add_executable(TCPClient class1-2/Client.cpp)
add_executable(TCPServer class1-2/Server.cpp)

add_executable(EchoClient class-3/echo_client.cpp)
add_executable(EchoServer class-3/echo_server.cpp)

add_executable(UDPClient class-4/udp_client.cpp)
add_executable(UDPServer class-4/udp_server.cpp)
add_executable(udp_server class-4/udp_server.cpp)