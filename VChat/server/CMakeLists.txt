cmake_minimum_required(VERSION 3.10)
project(Server)

set(CMAKE_CXX_STANDARD 17)
set(THIRDPARTYDIR ${CMAKE_SOURCE_DIR}/third_party)

include_directories(${THIRDPARTYDIR}/include)

file(GLOB_RECURSE SOURCE_FILES "server/*.cpp" "server/*.hpp")
add_executable(Server ${SOURCE_FILES})

# Only for M1 chip XOS
if (CMAKE_SYSTEM_NAME STREQUAL Darwin AND CMAKE_SYSTEM_PROCESSOR STREQUAL arm64)
    message("target arm64")
    set(CMAKE_OSX_ARCHITECTURES arm64)
    target_link_libraries(Server ${THIRDPARTYDIR}/sqlite3/libsqlite3.a)
endif ()
