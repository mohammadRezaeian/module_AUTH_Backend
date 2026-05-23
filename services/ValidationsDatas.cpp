//
// Created by root on 5/22/26.
//

#include "ValidationsDatas.h"

#include <iostream>

void ValidationsDatas::validateJsonBody(const std::shared_ptr<Json::Value> _json)
{
    if (!_json)
        throw std::runtime_error("Invalid JSON body");

    if (!_json->isObject())
        throw std::runtime_error("JSON must be object");


    if (!_json->isMember("email") || !(*_json)["email"].isString())
        throw std::runtime_error("email is required");

    if (!_json->isMember("password") || !(*_json)["password"].isString())
        throw std::runtime_error("password is required");

}

template<>
void ValidationsDatas::validateJson<RegisterRequest>(const RegisterRequest &dto)
{

    if (dto.getEmail().empty())
        throw std::runtime_error("Email cannot be empty");

    if (dto.getPassword().size() < 6)
        throw std::runtime_error("Password too short");
}

template<>
void ValidationsDatas::validateJson<LoginRequest>(const LoginRequest &dto)
{
}

template<>
void ValidationsDatas::validateJson<AuthResponse>(const AuthResponse &dto)
{

}

