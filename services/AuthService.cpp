#include "AuthService.h"


std::string AuthService::registerUser(const std::string& _email, const std::string& _password)
{
    std::tuple<bool,std::string> _response;
    auto existingUser = UserRepository::findByEmail(_email);
    if (existingUser.has_value())
    {
        throw std::runtime_error("User already exists");

    }

    User user;

    user.id = "1";
    user.m_email = _email;

    user.passwordHash = PasswordHasher::hash(_password);

    UserRepository::save(user);

    AuthResponse _generateToken;

    _generateToken.accessToken = JwtService::generateToken(user.id);


    return _generateToken.accessToken;
}

AuthResponse AuthService::loginUser(
    const LoginRequest& request
) {

    auto user =
        UserRepository::findByEmail(
            request.email
        );

    if (!user.has_value()) {
        throw std::runtime_error(
            "Invalid credentials"
        );
    }

    bool validPassword =
        PasswordHasher::verify(
            request.password,
            user->passwordHash
        );

    if (!validPassword) {
        throw std::runtime_error(
            "Invalid credentials"
        );
    }

    AuthResponse response;

    response.accessToken =
        JwtService::generateToken(
            user->id
        );

    return response;
}