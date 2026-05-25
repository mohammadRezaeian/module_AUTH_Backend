#ifndef AUTH_PASSWORDHASHER_H
#define AUTH_PASSWORDHASHER_H

#include <string>

class PasswordHasher {
public:
    std::string hash(const std::string& password);
    bool verify(const std::string& password, const std::string& hash);
};


#endif //AUTH_PASSWORDHASHER_H
