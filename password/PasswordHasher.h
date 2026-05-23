#ifndef AUTH_PASSWORDHASHER_H
#define AUTH_PASSWORDHASHER_H

#include <string>

class PasswordHasher {
public:
    static std::string hash(const std::string& password);

    static bool verify(const std::string& password, const std::string& hash);
};


#endif //AUTH_PASSWORDHASHER_H
