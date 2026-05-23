#ifndef AUTH_LOGINREQUEST_H
#define AUTH_LOGINREQUEST_H

#include  <string>
#include <stdexcept>
#include  <json/json.h>

class LoginRequest {
public:
    std::string email;
    std::string password;

    static LoginRequest fromJson(const Json::Value& json) {
        if (!json.isObject())
            throw std::runtime_error("Invalid JSON");

        if (!json.isMember("email") || !json.isMember("password"))
            throw std::runtime_error("missing fields");

        LoginRequest req;
        req.email = json["email"].asString();
        req.password = json["password"].asString();

        return req;
    }
};

#endif //AUTH_LOGINREQUEST_H
