#ifndef AUTH_AUTHRESPONSE_H
#define AUTH_AUTHRESPONSE_H

#include <string>

class AuthResponse {

private:
    std::string m_accessToken;

public:
    void setAccessToken(std::string _accessToken);
    [[nodiscard]] std::string getAccessToken() const;

};


#endif //AUTH_AUTHRESPONSE_H
