
#include "AuthResponse.h"


void AuthResponse::setAccessToken(std::string _accessToken)
{
    this->m_accessToken = _accessToken;
}
[[nodiscard]] std::string AuthResponse::getAccessToken() const
{
    return m_accessToken;
}
