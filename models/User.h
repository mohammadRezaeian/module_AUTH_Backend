#ifndef AUTH_USER_H
#define AUTH_USER_H

#include  <string>
#include <iostream>

class User {
public:
    std::string id;
    std::string m_email;
    std::string m_userName;
    std::string passwordHash;
};


#endif //AUTH_USER_H
