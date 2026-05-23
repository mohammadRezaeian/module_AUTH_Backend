#ifndef AUTH_JWTSERVICE_H
#define AUTH_JWTSERVICE_H


#include <string>
#include <optional>
#include <vector>
class JwtService {
public:

    static std::string generateToken(
        const std::string& userId
    );

    static bool verify(
        const std::string& token
    );
    static std::optional<std::string>
 extractUserId(
     const std::string& token
 );
    static std::vector<std::string>
extractRoles(
    const std::string& token
);
};
#endif //AUTH_JWTSERVICE_H
