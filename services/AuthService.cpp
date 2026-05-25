#include "AuthService.h"


std::string AuthService::registerUser(const std::string& _email, const std::string& _password, const std::string& _userName)
{
    std::tuple<bool,std::string> _response;
    auto _existingEmail = UserRepository::findByEmail(_email);
    if (_existingEmail.has_value())
    {
        throw std::runtime_error("Emai already exists");
    }
    auto _existingUserName = UserRepository::findByUserName(_userName);

    if (_existingUserName.has_value())
    {
        throw std::runtime_error("User already exists");
    }

    User _user;

    _user.setID("1");
    _user.setEmail(_email);

    _user.setPasswordHash( m_passwordHasher.hash(_password) );
    _user.setUserName(_userName);
    UserRepository::save(_user);

    AuthResponse _generateToken;

    _generateToken.setAccessToken( m_jwtService.generateToken(_user.getID()) );


    return _generateToken.getAccessToken();
}

std::string AuthService::loginUser(const std::string& _email, const std::string& _password, const std::string& _userName)
{
    bool _validPassword;
    AuthResponse _generateToken;

    if (_email.empty() && _userName.empty())
    {
        throw std::runtime_error("Email Or UserName is empty");
    }
    if (!_email.empty())
    {
        auto _user = UserRepository::findByEmail(_email);
        if (_user.has_value())
        {
            _validPassword = m_passwordHasher.verify(_password,_user->getPasswordHash());
            _generateToken.setAccessToken( m_jwtService.generateToken(_user->getID()) );
        }

        if (!_validPassword)
        {
            throw std::runtime_error("Invalid credentials");
        }

    }
    else if (!_userName.empty())
    {
        auto _user = UserRepository::findByUserName(_userName);
        if (_user.has_value() )
        _validPassword = m_passwordHasher.verify(_password,_user->getPasswordHash());
        _generateToken.setAccessToken( m_jwtService.generateToken(_user->getID()));
    }
    else
    {
        throw std::runtime_error("User Or Email wasn't exists");
    }
    return _generateToken.getAccessToken();
}