cmake_minimum_required(VERSION 3.0)
project(DShell VERSION 1.0)

find_package(curses)

message("courses_found = ${CURSES_FOUND}")

if((NOT ${CURSES_FOUND}) EQUAL TRUE)
message(ERROR "curses not find.May be you should install ncurses-devel")
endif()

message("ncurses/ncurses.h = ${CURSES_HAVE_NCURSES_NCURSES_H}")
message("ncurses.h = ${CURSES_HAVE_NURSES_H}")

if("${CURSES_HAVE_NCURSES_NCURSES_H}" EQUAL "TRUE")
include(${CURSES_HAVE_NCURSES_NCURSES_H})
endif()

if("${CURSES_HAVE_NURSES_H}" EQUAL "TRUE")
include(${CURSES_HAVE_NURSES_H})
endif()

add_executable(Dsh dshell.cpp)

target_link_libraries(Dsh ${CURSES_LIBRARIES})
