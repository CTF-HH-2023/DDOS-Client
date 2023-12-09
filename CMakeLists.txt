cmake_minimum_required(VERSION 3.26)
project(DDOS_Client C)

set(CMAKE_C_STANDARD 11)

find_package(CURL REQUIRED)

add_executable(DDOS_Client ddos.c)
target_link_libraries(DDOS_Client CURL::libcurl)
