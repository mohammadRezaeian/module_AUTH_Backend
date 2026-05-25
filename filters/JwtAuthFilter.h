#ifndef AUTH_JWTAUTHFILTER_H
#define AUTH_JWTAUTHFILTER_H


#include <drogon/HttpFilter.h>
#include "services/JwtService.h"
#include "models/CurrentUser.h"


class JwtAuthFilter : public drogon::HttpFilter<JwtAuthFilter> {
public:
    void doFilter(const drogon::HttpRequestPtr& req, drogon::FilterCallback&& fcb, drogon::FilterChainCallback&& fccb) override;
    JwtService m_jwtService;
};

#endif //AUTH_JWTAUTHFILTER_H
