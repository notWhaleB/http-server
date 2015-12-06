#include "parse.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string define_MIME(const std::string &file) {
    std::string ext;
    for (auto i = file.rbegin(); i != file.rend() && *i != '.'; ++i) {
        ext.push_back(*i);
    }
    std::reverse(ext.begin(), ext.end());

    if (ext == "html") {
        return "text/html";
    } else if (ext == "js") {
        return "application/javascript";
    } else if (ext == "css") {
        return "text/css";
    } else if (ext == "jpg" || ext == "jpeg") {
        return "image/jpeg";
    } else if (ext == "png" || ext == "gif" ||
               ext == "svg" || ext == "tiff") {
        return "image/" + ext;
    } else {
        return "none";
    }
}