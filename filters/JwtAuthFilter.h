#ifndef AUTH_JWTAUTHFILTER_H
#define AUTH_JWTAUTHFILTER_H


#include <drogon/HttpFilter.h>

using namespace drogon;

class JwtAuthFilter : public HttpFilter<JwtAuthFilter> {
public:
    void doFilter(
        const HttpRequestPtr& req,
        FilterCallback&& fcb,
        FilterChainCallback&& fccb
    ) override;
};

#endif //AUTH_JWTAUTHFILTER_H
