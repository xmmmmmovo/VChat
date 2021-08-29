cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OSX_ARCHITECTURES arm64)

# include_directories(/usr/local/include ./include)
# include_directories("/opt/homebrew/include")
include_directories("./include")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_executable(Server ${SOURCE_FILES})
