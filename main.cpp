#include <iostream>

#include "include/Server.h"

int main(int argc, char const *argv[]){
    std::stringstream ss(argv[1]);
    int port;
    ss >> port;
    Server serv;
    serv.bind("/", [] (http::Request) {
        http::Response res;
        std::stringstream message;
        message << "<h1>Hey! Welcome to the site. <a href=\"info\">Click Me!</a></h1>";
        res.write(message);
        return res.generate();
    });

    serv.bind("/info", [] (http::Request) {
        http::Response res;
        std::stringstream message;
        message << "<h1>Hello World, I'm a Http Server Written in C++.</h1>";
        res.write(message);
        return res.generate();
    });

    serv.listen(port);
    return 0;
}
