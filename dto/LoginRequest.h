#ifndef AUTH_LOGINREQUEST_H
#define AUTH_LOGINREQUEST_H

#include  <string>
#include <stdexcept>
#include  <json/json.h>

class LoginRequest {
private:
    std::string m_email;
    std::string m_userName;
    std::string m_password;

public:
    void parseJson(const Json::Value& json);

    [[nodiscard]] std::string getUsername() const;
    [[nodiscard]] std::string getEmail() const;
    [[nodiscard]] std::string getPassword() const;

};

#endif //AUTH_LOGINREQUEST_H
