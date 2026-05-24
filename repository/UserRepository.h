#ifndef AUTH_USERREPOSITORY_H
#define AUTH_USERREPOSITORY_H

#include  "models/User.h"
#include <optional>
#include <vector>

class UserRepository {
public:
    static void save(const User& user);
    static std::optional<User> findByEmail(const std::string& _email);
    static std::optional<User> findByUserName(const std::string& _username);

private:
    static std::vector<User> users;
};


#endif //AUTH_USERREPOSITORY_H
