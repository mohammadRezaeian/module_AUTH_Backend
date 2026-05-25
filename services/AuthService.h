#ifndef AUTH_ATUHSERVICE_H
#define AUTH_ATUHSERVICE_H

#include  "../dto/AuthResponse.h"
#include  "../dto/RegisterRequest.h"
#include  "dto/LoginRequest.h"
#include "services/JwtService.h"
#include "models/User.h"
#include "password/PasswordHasher.h"
#include "repository/UserRepository.h"
#include <stdexcept>
#include <unordered_map>
#include "services/JwtService.h"

class AuthService {
private:
    // std::unordered_map<std::string, std::string> values;
    PasswordHasher m_passwordHasher;
    JwtService     m_jwtService;
public:
    std::string registerUser(const std::string& _email, const std::string& _password, const std::string& _userName);
    std::string loginUser(const std::string& _email, const std::string& _password, const std::string& _userName={""});
};


#endif //AUTH_ATUHSERVICE_H
