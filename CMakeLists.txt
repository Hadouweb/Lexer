cmake_minimum_required(VERSION 3.0)
project(lexer)

add_subdirectory(libft)

set(SRCS
    srcs/main.c)

add_executable(lexer ${SRCS})

target_link_libraries(lexer ft)