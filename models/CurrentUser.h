#ifndef AUTH_CURRENTUSER_H
#define AUTH_CURRENTUSER_H


#include <string>
#include <vector>

class CurrentUser
{
private:
    std::string m_userId;
    std::vector<std::string> m_roles;
    std::string m_expireAt;
public:
    [[nodiscard]] std::string getUserID() const;
    [[nodiscard]] std::vector<std::string> getRoles() const;
    [[nodiscard]] std::string getExpireAt() const;

    void setUserID(std::string _userId);
    void setRoles(std::vector<std::string> _roles) ;
    void setExpireAt(std::string _expireAt);


};

#endif //AUTH_CURRENTUSER_H
