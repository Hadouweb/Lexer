cmake_minimum_required(VERSION 3.0)
project(lexer)

include_directories(includes)
add_subdirectory(libft)

set(SRCS
    srcs/main.c
    srcs/lex.c
    )

set(HEADERS
    includes/lexer.h)

add_executable(lexer ${SRCS} ${HEADERS})

target_link_libraries(lexer ft)