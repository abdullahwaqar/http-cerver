#ifndef HTTP_H
#define HTTP_H

#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <iterator>

namespace http{
    class Request {

        static std::vector<std::string> spaceSplit(std::string line);
        static std::vector<std::string> getLines(std::string req);
        friend std::ostream& operator << (std::ostream &os, const Request &req);

        public:
            static Request reqFromString(std::string str);

            inline std::string method() const {
            return method_;
            }

            inline std::string path() const {
                return path_;
            }

            inline std::string version() const {
                return version_;
            }

            inline std::unordered_map<std::string, std::string> fields() const {
                return fields_;
            }

      private:

        Request(std::string meth, std::string route, std::string ver, std::unordered_map<std::string, std::string> fields);

        std::unordered_map<std::string, std::string> fields_;
        std::string method_;
        std::string path_;
        std::string version_;
    };

    class Response {
        public:
            Response();
            std::string generate();
            void setContentType(std::string ext);
            void write(std::istream& s);
        private:
            std::string content_type_;
            std::stringstream Response_stream_;
    };
}
#endif //HTTP_H