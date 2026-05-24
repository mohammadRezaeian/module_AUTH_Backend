#include "LoginRequest.h"

void LoginRequest::parseJson(const Json::Value& json)
{
    this->m_email = json["email"].asString();
    this->m_userName = json["userName"].asString();
    this->m_password = json["password"].asString();
}

[[nodiscard]] std::string LoginRequest::getUsername() const
{
    return m_userName;
}
[[nodiscard]] std::string LoginRequest::getEmail() const
{
    return m_email;
}

[[nodiscard]] std::string LoginRequest::getPassword() const
{
    return m_password;
}
