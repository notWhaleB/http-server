#ifndef __HttpServer__parse__
#define __HttpServer__parse__

#include "main.h"

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

std::string define_MIME(const std::string &file);

#endif
