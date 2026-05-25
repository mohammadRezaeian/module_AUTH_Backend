#include "JwtAuthFilter.h"

void JwtAuthFilter::doFilter(const drogon::HttpRequestPtr& req, drogon::FilterCallback&& fcb, drogon::FilterChainCallback&& fccb)
{
    const auto authHeader = req->getHeader("Authorization");

    if (authHeader.empty())
    {
        auto _resp = drogon::HttpResponse::newHttpResponse();
        _resp->setStatusCode(drogon::k401Unauthorized);
        _resp->setBody("Missing Authorization header");
        fcb(_resp);
        return;
    }

    const std::string _bearerPrefix = "Bearer ";

    if (authHeader.rfind(_bearerPrefix, 0) != 0)
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k401Unauthorized);
        resp->setBody("Invalid Authorization format");
        fcb(resp);
        return;
    }

    const std::string _token = authHeader.substr(_bearerPrefix.size());

    if (!m_jwtService.verify(_token))
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k401Unauthorized);
        resp->setBody("Invalid or expired token");
        fcb(resp);
        return;
    }

    auto _userIdOpt = m_jwtService.extractUserId(_token);
    if (!_userIdOpt.has_value())
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k401Unauthorized);
        resp->setBody("Invalid token payload");
        fcb(resp);
        return;
    }

    auto _userRoles = m_jwtService.extractRoles(_token);
    if (!_userRoles.has_value())
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k401Unauthorized);
        resp->setBody("Invalid token payload");
        fcb(resp);
        return;
    }

    auto _userExpireAt = m_jwtService.extractExpirAt(_token);
    if (!_userExpireAt.has_value())
    {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setStatusCode(drogon::k401Unauthorized);
        resp->setBody("Invalid token payload");
        fcb(resp);
        return;
    }

    CurrentUser _currentUser;
    _currentUser.settUserID(_userIdOpt.value());
    _currentUser.settRoles(_userRoles.value());
    _currentUser.setExpireAt(_userExpireAt.value());

    req->getAttributes()->insert("currentUser", _currentUser);

    fccb();
}