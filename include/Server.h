#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <fstream>
#include <functional>
#include <unordered_map>

#include "Http.h"
#include "tcp_socket.h"

class Server {
  public:
    Server();
    ~Server();

    bool bound(std::string route);
    void bind(std::string route, std::function<std::string(http::Request)> const& func);
    void listen(int portNumber);

    std::string handle(http::Request& req, std::string route);
  private:
    std::unordered_map<std::string, std::function<std::string(http::Request)>> routes_;
};

#endif //SERVER_H