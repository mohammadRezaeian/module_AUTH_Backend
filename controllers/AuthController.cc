#include "AuthController.h"
#include  <services/JwtService.h>

void V1::AUTHAPI::AuthController::registerUser(const drogon::HttpRequestPtr& req,std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    try {
        auto json = req->getJsonObject();

        m_validationsDatas.validateJsonBody(json);
        m_registerRequest.parseJson(*json);
        m_validationsDatas.validateJson(m_registerRequest);
        sendMessagesResponse("accessToken" , m_authService.registerUser(m_registerRequest.getEmail(), m_registerRequest.getPassword()), std::move(callback));
    }
    catch (const std::exception& e)
    {
        sendMessageErrors(e.what(), std::move(callback));
    }
}

void V1::AUTHAPI::AuthController::loginUser(const drogon::HttpRequestPtr& req,std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    try {
        auto json = req->getJsonObject();

        LoginRequest request = LoginRequest::fromJson(*json);

        auto result = AuthService::loginUser(request);
        Json::Value response;
        response["accessToken"] = result.accessToken;

        auto resp =
            drogon::HttpResponse::newHttpJsonResponse(response);

        callback(resp);
    }
    catch (const std::exception& e)
        {
        Json::Value err;
        err["error"] = e.what();

        auto resp =drogon::HttpResponse::newHttpJsonResponse(err);
        resp->setStatusCode(drogon::k401Unauthorized);

        callback(resp);
    }
}

void V1::AUTHAPI::AuthController::me(
    const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback
) {
    auto currentUser =
        req->getAttributes()->get<CurrentUser>("currentUser");

    Json::Value res;
    res["userId"] = currentUser.userId;

    for (const auto& role : currentUser.roles)
        res["roles"].append(role);

    res["expireAt"] = currentUser.expireAt;

    callback(drogon::HttpResponse::newHttpJsonResponse(res));
}

void V1::AUTHAPI::AuthController::sendMessagesResponse(const std::string &&_typeMessage, const std::string &&_message, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value message;
    message[_typeMessage]= _message;

    auto resp = drogon::HttpResponse::newHttpJsonResponse(message);
    callback(resp);
}


void V1::AUTHAPI::AuthController::sendMessageErrors(const std::string &&_message, std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value message;
    message["error"]= _message;

    auto resp = drogon::HttpResponse::newHttpJsonResponse(message);
    resp->setStatusCode(drogon::k400BadRequest);
    callback(resp);
}
