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

class AuthService {
private:
    std::unordered_map<std::string, std::string> values;

public:
    std::string registerUser(const std::string& _request, const std::string& _password);
    static AuthResponse loginUser(const LoginRequest& request);
};


#endif //AUTH_ATUHSERVICE_H
