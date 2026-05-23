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
        if (user.m_email == email)
        {
            return user;
        }
    }

    return std::nullopt;
}