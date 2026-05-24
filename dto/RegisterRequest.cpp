#include "RegisterRequest.h"


void RegisterRequest::parseJson(const Json::Value& json)
{

    this->m_email = json["email"].asString();
    this->m_userName = json["userName"].asString();
    this->m_password = json["password"].asString();

}

[[nodiscard]] std::string RegisterRequest::getUsername() const
{
    return m_userName;
}
[[nodiscard]] std::string RegisterRequest::getEmail() const
{
    return m_email;
}

[[nodiscard]] std::string RegisterRequest::getPassword() const
{
    return m_password;
}
