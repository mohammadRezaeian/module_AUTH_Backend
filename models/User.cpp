#include "User.h"

void User::setID          (const std::string&& _value)
{
    m_id = _value;
}
void User::setEmail       (const std::string& _value)
{
    m_email = _value;
}
void User::setUserName    (const std::string& _value)
{
    m_userName = _value;
}
void User::setPasswordHash(const std::string& _value)
{
    m_passwordHash = _value;
}

[[nodiscard]] std::string User::getID() const {
    return m_id;
}

[[nodiscard]] std::string User::getEmail() const {
    return m_email;
}

[[nodiscard]] std::string User::getUserName() const {
    return m_userName;
}

[[nodiscard]] std::string User::getPasswordHash() const {
    return m_passwordHash;
}

