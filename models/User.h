#ifndef AUTH_USER_H
#define AUTH_USER_H

#include  <string>
#include <iostream>

class User {
public:
    [[nodiscard]] std::string getID() const;
    [[nodiscard]] std::string getEmail() const ;
    [[nodiscard]] std::string getUserName() const ;
    [[nodiscard]] std::string getPasswordHash() const ;


    void setID          (const std::string&& _value);
    void setEmail       (const std::string& _value);
    void setUserName    (const std::string& _value);
    void setPasswordHash(const std::string& _value);
private:
    std::string m_id;

    std::string m_email;
    std::string m_userName;
    std::string m_passwordHash;

};


#endif //AUTH_USER_H
