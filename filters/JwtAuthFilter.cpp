#include "JwtAuthFilter.h"

#include "services/JwtService.h"
#include "models/CurrentUser.h"

void JwtAuthFilter::doFilter(
    const HttpRequestPtr& req,
    FilterCallback&& fcb,
    FilterChainCallback&& fccb
) {
    const auto authHeader = req->getHeader("Authorization");

    if (authHeader.empty()) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k401Unauthorized);
        resp->setBody("Missing Authorization header");
        fcb(resp);
        return;
    }

    const std::string bearerPrefix = "Bearer ";

    if (authHeader.rfind(bearerPrefix, 0) != 0) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k401Unauthorized);
        resp->setBody("Invalid Authorization format");
        fcb(resp);
        return;
    }

    const std::string token =
        authHeader.substr(bearerPrefix.size());

    if (!JwtService::verify(token)) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k401Unauthorized);
        resp->setBody("Invalid or expired token");
        fcb(resp);
        return;
    }

    auto userIdOpt = JwtService::extractUserId(token);
    if (!userIdOpt.has_value()) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k401Unauthorized);
        resp->setBody("Invalid token payload");
        fcb(resp);
        return;
    }

    CurrentUser currentUser;
    currentUser.userId = userIdOpt.value();
    currentUser.roles = JwtService::extractRoles(token);

    req->getAttributes()->insert("currentUser", currentUser);

    fccb();
}