#include "JwtService.h"
#include <jwt-cpp/jwt.h>
#include <nlohmann/json.hpp>

namespace {

    const std::string SECRET =
        "CHANGE_THIS_LONG_SECRET";

}

std::string JwtService::generateToken(
    const std::string& userId
) {
    nlohmann::json roles = {"user", "admin"};

    nlohmann::json rolesJson = roles;
    auto token = jwt::create()
        .set_type("JWT")
        .set_issuer("auth-service")
        .set_subject(userId)
        .set_payload_claim("roles",jwt::claim(roles.dump()))
        .set_expires_at(std::chrono::system_clock::now()+ std::chrono::minutes(15))
        .sign(jwt::algorithm::hs512{SECRET}
            );

    return token;
}

bool JwtService::verify(const std::string& token)
{

    try {

        auto decoded = jwt::decode(token);

        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs512{SECRET})
            .with_issuer("auth-service");

        verifier.verify(decoded);

        auto exp = decoded.get_expires_at();

        auto now = std::chrono::system_clock::now();

        if (now >= exp) {
            return false;
        }
        return true;

    } catch (...) {
        return false;
    }
}
std::optional<std::string>
JwtService::extractUserId(
    const std::string& token
) {

    try {

        auto decoded = jwt::decode(token);

        return decoded.get_subject();

    } catch (...) {
        return std::nullopt;
    }
}

std::vector<std::string>
JwtService::extractRoles(const std::string& token)
{
    std::vector<std::string> roles;

    try {
        auto decoded = jwt::decode(token);

        auto claim = decoded.get_payload_claim("roles");


        auto rolesStr = claim.as_string();

        auto j = nlohmann::json::parse(rolesStr);

        roles = j.get<std::vector<std::string>>();

    } catch (...) {
    }

    return roles;
}