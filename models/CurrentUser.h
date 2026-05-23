#ifndef AUTH_CURRENTUSER_H
#define AUTH_CURRENTUSER_H


#include <string>
#include <vector>

class CurrentUser {
public:

    std::string userId;

    std::vector<std::string> roles;
    std::string expireAt;
};

#endif //AUTH_CURRENTUSER_H
