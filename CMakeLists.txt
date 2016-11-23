cmake_minimum_required(VERSION 3.0)
project(lexer)

include_directories(includes)
add_subdirectory(libft)
add_subdirectory(unit_test)

set(SRCS
    srcs/main.c
    srcs/lex.c
    srcs/debug.c
    srcs/token_func1.c
    srcs/init_lex.c
    srcs/util_lex.c
    )

set(HEADERS
    includes/lexer.h)

add_executable(lexer ${SRCS} ${HEADERS})

target_link_libraries(lexer ft)