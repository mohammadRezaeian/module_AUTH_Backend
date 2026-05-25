#include "CurrentUser.h"

[[nodiscard]] std::string CurrentUser::getUserID() const
{
    return m_userId;
}

[[nodiscard]] std::vector<std::string> CurrentUser::getRoles() const
{
    return m_roles;
}

[[nodiscard]] std::string CurrentUser::getExpireAt() const
{
    return m_expireAt;
}

void CurrentUser::settUserID(std::string _userId)
{
    this->m_userId = _userId;
}
void CurrentUser::settRoles(std::vector<std::string> _roles)
{
    this->m_roles = _roles;

}
void CurrentUser::setExpireAt(std::string _expireAt)
{
    this->m_expireAt = _expireAt;

}
