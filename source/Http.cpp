#include "../include/Http.h"

using std::string;
using std::unordered_map;

namespace http {

std::vector<string> Request::spaceSplit(std::string line) {
    std::vector<string> vals;
    string one, two;
    std::stringstream ss(line);
    ss >> one;
    ss >> two;
    vals.push_back(one);
    vals.push_back(two);
    std::cout << one << "," << two << "added to the map" << std::endl;
    return vals;
}

std::vector<string> Request::getLines(string str) {
    std::istringstream ss(str);
    std::vector<string> lines;
    std::string line;
    while (getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}

std::ostream& operator << (std::ostream &os, const Request &req) {
    os << "Method, Path, version" << req.method() << ", " << req.path() << "," << req.version() << std::endl;
    std::unordered_map<std::string, std::string> fields = req.fields();
    for (auto it = fields.begin(); it != fields.end(); ++it) {
        os << it->first << " : " << it->second << std::endl;
    }
    return os;
}

Request Request::reqFromString(string str_req) {
    unordered_map<string, string> field_map;
    std::vector<string> lines = getLines(str_req);
    std::stringstream req_line(lines[0]);
    string method, path, version;
    req_line >> method;
    req_line >> path;
    req_line >> version;
    // GET HTTP/1.1
    for (unsigned int i = 1; i < lines.size(); i++) {
        std::vector<string> entry = spaceSplit(lines[i]);
        field_map.emplace(entry[0], entry[1]);
    }
    return Request(method, path, version, field_map);
}

Request::Request(string meth, string route, string ver, std::unordered_map<string, string> field_map) : fields_(field_map), method_(meth), path_(route), version_(ver) {}

Response::Response() : content_type_("text/html"),Response_stream_() {}

void Response::write(std::istream& s) {
    string str((std::istreambuf_iterator<char>(s)),
    std::istreambuf_iterator<char>());
    Response_stream_ << str;
}

void Response::setContentType(std::string ext) {
    std::string type = "text/plain";
    if (ext == "html") {
      type = "text/html";
    }
    else if (ext == "js") {
      type = "text/javascript";
    }
    else if (ext == "css") {
      type = "text/css";
    }
    else if (ext == "jpeg" || ext == "jpg" || ext == "png" || ext == "gif") {
      type = "image/" + ext;
    }
    content_type_ = type;
}

string Response::generate() {
  return "HTTP/1.1 200 OK\nContent-Type: "+content_type_+";\n\n" + Response_stream_.str();
}
}