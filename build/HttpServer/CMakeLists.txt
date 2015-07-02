cmake_minimum_required (VERSION 2.6)

set (PROJECT HttpServer)

project (${PROJECT})

set (HEADERS
../../main.h
../../server.h)

set (SOURCES
../../main.cpp
../../server.cpp)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
