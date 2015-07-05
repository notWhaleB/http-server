Program("server", ["main.cpp", "server.cpp"], CXXFLAGS="-std=c++0x", CXXPATH=".")
Program("run_test", ["server.cpp", "tests.cpp", "gtest-all.cc"], CXXFLAGS="-std=c++0x", LIBS="pthread")