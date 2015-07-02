cmake_minimum_required (VERSION 2.6)

set (PROJECT HttpServerTests)

project (${PROJECT})

set (HEADERS
../../gtest.h
../../main.h
../../server.h)

set (SOURCES
../../gtest-all.cc
../../tests.cpp
../../server.cpp)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
