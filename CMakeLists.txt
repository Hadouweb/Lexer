cmake_minimum_required(VERSION 3.0)
project(lexer)

include_directories(includes)
add_subdirectory(libft)
add_subdirectory(unit_test)

set(SRCS
    srcs/main.c
    srcs/lexer.c
    srcs/debug.c
    srcs/token_func1.c
    srcs/init_lexer.c
        srcs/util_lexer.c
    srcs/main_loop_lex.c
    srcs/parser.c
    srcs/init_parser.c
    srcs/rule_func1.c
    )

set(HEADERS
    includes/lexer.h)

add_executable(lexer ${SRCS} ${HEADERS})

target_link_libraries(lexer ft)