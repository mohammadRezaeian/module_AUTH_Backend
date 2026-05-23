#ifndef AUTH_REGISTERREQUEST_H
#define AUTH_REGISTERREQUEST_H


#include <string>
#include <stdexcept>
#include <json/json.h>

class RegisterRequest {

private:
    std::string m_username;
    std::string m_email;
    std::string m_password;

public:
    void parseJson(const Json::Value& json);

    [[nodiscard]] std::string getUsername() const;
    [[nodiscard]] std::string getEmail() const;
    [[nodiscard]] std::string getPassword() const;

};


#endif //AUTH_REGISTERREQUEST_H
