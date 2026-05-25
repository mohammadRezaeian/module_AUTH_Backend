#include "UserRepository.h"

std::vector<User> UserRepository::users;

void UserRepository::save(const User& user)
{
    users.push_back(user);
}

std::optional<User>UserRepository::findByEmail(const std::string& email)
{
    for (const auto& user : users)
        {
        if (user.getEmail() == email)
        {
            return user;
        }
    }
    return std::nullopt;
}


std::optional<User>UserRepository::findByUserName(const std::string& _username)
{
    for (const auto& user : users)
    {
        if (user.getUserName() == _username)
        {
            return user;
        }
    }
    return std::nullopt;
}
