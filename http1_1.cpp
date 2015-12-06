#include "http1_1.h"

const size_t READS_LIMIT = 256;
std::string homePageFile = "index.html";
std::string sitePath = "site/";

void http_reply(int clientDescriptor, HttpResponse response, const std::string &MIME, std::string &content) {
    std::string header;
    switch (response) {
        case OK: header += "HTTP/1.1 200 OK\r\n"; break;
        case BAD_REQUEST: header += "HTTP/1.1 400 Bad Request\r\n"; break;
        case FORBIDDEN: header += "HTTP/1.1 403 Forbidden\r\n"; break;
        case METHOD_NOT_ALLOWED: header += "HTTP/1.1 405 Method Not Allowed\r\n"; break;
        case NOT_FOUND: header += "HTTP/1.1 404 Not Found\r\n"; break;
        case HTTP_VER_NOT_SUPPORTED: header += "HTTP/1.1 505 HTTP Version Not Supported\r\n"; break;
    }

    header += "Content-Type: " + MIME + "; charset=utf-8\r\n";
    header += "Content-Length: " + std::to_string(content.size()) + "\r\n";
    header += "Connection: close\r\n";

    write_all(clientDescriptor, header + "\r\n" + content);
}



int get_file(std::string path, std::string &buf) {
    if (path.length() == 0) return -1;

    std::ifstream in;
    in.open(runPath + path);

    if (!in.is_open()) {
        in.close();
        return -1;
    }
    while (!in.eof()) {
        buf += (in.get());
    }
    buf.pop_back();

    in.close();
    return 0;
}

void process_error(int clientDescriptor, HttpResponse error) {
    std::string buf;
    get_file(std::to_string(error) + ".html", buf);
    http_reply(clientDescriptor, error, "text/html", buf);
    wr_close(clientDescriptor);
}

std::vector<std::string> get_request_lines(int clientDescriptor) {
    std::string request;
    char buf[BUF_SIZE];

    for (size_t i = 0; i != READS_LIMIT; ++i) {
        ssize_t readSize = read(clientDescriptor, buf, BUF_SIZE);
        for (size_t i = 0; i != readSize; ++i) {
            request += buf[i];
        }
        if (request.length() == 0) {
            break;
        } else if (request.length() == 1) {
            if (request[0] == '\n') break;
        } else if (request.length() == 2) {
            if (request == "\r\n" || request == "\n\n") break;
        } else if (request.length() >= 3) {
            std::string last_three = request.substr(request.length() - 3, 3);
            if (last_three == "\r\n\n" || last_three == "\n\r\n" || last_three == "\n\n\n"
                || last_three.substr(1, 2) == "\n\n") break;
        }
    }

    std::vector<std::string> lines = split(request, '\n');
    for (auto &i : lines) {
        if (i.back() == '\r') {
            i.pop_back();
        }
    }

    return lines;
}

bool check_request(int clientDescriptor, std::vector<std::string> &lines,
                   std::vector<std::string> &startString) {
    if (lines.size() == 0) {
        process_error(clientDescriptor, BAD_REQUEST);
        return false;
    }
    if (startString.size() != 3) {
        process_error(clientDescriptor, BAD_REQUEST);
        return false;
    }
    if (startString[0] != "GET") {
        process_error(clientDescriptor, METHOD_NOT_ALLOWED);
        return false;
    }
    if (startString[2] != "HTTP/0.9" && startString[2] != "HTTP/1.0" &&
        startString[2] != "HTTP/1.1" && startString[2] != "HTTP/1.x") {
        process_error(clientDescriptor, HTTP_VER_NOT_SUPPORTED);
        return false;
    }

    return true;
}

void http1_1_handler(int clientDescriptor) {

    std::vector<std::string> lines = get_request_lines(clientDescriptor);

    std::vector<std::string> startString = split(lines[0], ' ');
    if (!check_request(clientDescriptor, lines, startString)) {
        return;
    }
    std::string requestPath = startString[1];

    if (requestPath[0] == '/') {
        requestPath = requestPath.substr(1, requestPath.length() - 1);
    }
    for (size_t i = 1; i < requestPath.length(); ++i) {
        if (requestPath[i] == '.' && requestPath[i - 1] == '.') {
            process_error(clientDescriptor, FORBIDDEN);
            return;
        }
    }
    if (requestPath == "") {
        requestPath += homePageFile;
    }
    std::string mime = define_MIME(requestPath);
    if (mime == "none") {
        requestPath += ".html";
        mime = "text/html";
    }

    std::string fileBuf;

    if (get_file(sitePath + requestPath, fileBuf) == -1) {
        process_error(clientDescriptor, NOT_FOUND);
        return;
    }

    http_reply(clientDescriptor, OK, mime, fileBuf);
    wr_close(clientDescriptor);
}