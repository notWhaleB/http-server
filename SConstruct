Program("server", ["main.cpp", "server.cpp", "wrappers.cpp", "echo.cpp", "http1_1.cpp", "parse.cpp"], CXXFLAGS="-std=c++0x", CXXPATH=".")
Program("run_test", ["server.cpp", "tests.cpp", "wrappers.cpp", "echo.cpp", "http1_1.cpp", "parse.cpp", "gtest-all.cc"], CXXFLAGS="-std=c++0x", LIBS="pthread")
