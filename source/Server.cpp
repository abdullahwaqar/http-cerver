#include "../include/Server.h"

Server::Server() : routes_() {}

Server::~Server() {}

void Server::bind(string route, std::function<string(http::Request)> const& handler) {
    if (route[0] == '/') route = route.substr(1);
    routes_.emplace(route, handler);
}

bool Server::bound(string path) {
    return routes_.count(path) > 0;
}

void Server::listen(int portNumber) {
    const int MAX_REQUEST_LEN = 1000;
    const int MAX_WAIT = 5;
    // catch unable to connect
    TCPServerSocket socket("localhost", portNumber, MAX_WAIT);
    char buffer[MAX_REQUEST_LEN];
    while (true) {
        std::cout << "Accepting Connections on " << socket.getLocalAddress() << ":" << socket.getLocalPort() << std::endl;
        TCPSocket *client = socket.accept();
        std::cout << client->getForeignAddress() << ":" << client->getForeignPort() << " Connected" << std::endl;
        client->recv(buffer, MAX_REQUEST_LEN);
        http::Request req = http::Request::reqFromString(std::string(buffer));
        //protect a bit from malformed paths
        std::string route = req.path();
        size_t dot = route.find(".");
        std::string ext = "";
        if (dot != std::string::npos) {
            ext = route.substr(dot + 1);
        }
        if (route[0] == '/') route = route.substr(1);
        std::string resBody = "HTTP/1.1 404 Not Found\n\n";
        if (bound(route)) {
            resBody = handle(req, route);
        }
        else {
            std::ifstream file;
            file.open(route);
            if (file.good()) {
                http::Response res;
                if (ext != "") {
                    std::cout << ext << std::endl;
                    res.setContentType(ext);
                }
                res.write(file);
                resBody = res.generate();
            }
        }
        int len = resBody.length();
        client->send(resBody.c_str(), len+1);
        delete client;
        std::cout << buffer << std::endl;
    }
}

string Server::handle(http::Request& req, string route) {
    return routes_.at(route)(req);
}