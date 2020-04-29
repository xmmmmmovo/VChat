cmake_minimum_required(VERSION 3.10)
project(NetCodeWindows)

set(CMAKE_CXX_STANDARD 14)

add_executable(server server.cpp)
target_link_libraries(server ws2_32.lib)

add_executable(client client.cpp)
target_link_libraries(client ws2_32.lib)