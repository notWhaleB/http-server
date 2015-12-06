#ifndef __HttpServer__http1_1__
#define __HttpServer__http1_1__

#include "main.h"
#include "parse.h"

#include <vector>
#include <fstream>

enum HttpResponse {OK = 200, BAD_REQUEST = 400, FORBIDDEN = 403, METHOD_NOT_ALLOWED = 405, NOT_FOUND = 404, HTTP_VER_NOT_SUPPORTED = 505};

void http1_1_handler(int clientDescriptor);

#endif
