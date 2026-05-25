#ifndef AUTH_JWTSERVICE_H
#define AUTH_JWTSERVICE_H


#include <string>
#include <optional>
#include <vector>
#include <jwt-cpp/jwt.h>
#include <nlohmann/json.hpp>

class JwtService {
public:
    std::string generateToken( const std::string& userId );

     bool verify(const std::string& token);
     std::optional<std::string> extractUserId(const std::string& token);
     std::optional<std::vector<std::string>>   extractRoles(const std::string& token);
     std::optional<std::string> extractExpirAt(const std::string& token);

};
#endif //AUTH_JWTSERVICE_H
