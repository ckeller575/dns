cmake_minimum_required(VERSION 3.0)
project(dns)

add_executable(client src/client.c)
add_executable(server src/server.c)
