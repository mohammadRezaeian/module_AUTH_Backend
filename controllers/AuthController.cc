#include "AuthController.h"
#include  <services/JwtService.h>

void V1::AUTHAPI::AuthController::registerUser(const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    try
    {
        auto json = req->getJsonObject();

        m_validationsDatas.validateJsonBody(json);
        m_registerRequest.parseJson(*json);
        m_validationsDatas.validateJson(m_registerRequest);
        sendMessagesResponse("accessToken", m_authService.registerUser(
            m_registerRequest.getEmail(), m_registerRequest.getPassword(),
            m_registerRequest.getUsername()), std::move(callback));
    }
    catch (const std::exception& e)
    {
        sendMessageErrors(e.what(), std::move(callback));
    }
}

void V1::AUTHAPI::AuthController::loginUser(const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    try
    {
        auto json = req->getJsonObject();

        m_validationsDatas.validateJsonBodyLogin(json);
        m_LoginRequest.parseJson(*json);
        m_validationsDatas.validateJson(m_LoginRequest);
        sendMessagesResponse("accessToken", m_authService.loginUser(
            m_LoginRequest.getEmail(), m_LoginRequest.getPassword(),
            m_LoginRequest.getUsername()), std::move(callback));

    }
    catch (const std::exception& e)
    {
       sendMessageErrors(e.what(), std::move(callback));
    }
}

void V1::AUTHAPI::AuthController::me(const drogon::HttpRequestPtr& req,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    auto _currentUser = req->getAttributes()->get<CurrentUser>("currentUser");

    Json::Value _res;
    _res["userId"] = _currentUser.getUserID();

    for (const auto& role : _currentUser.getRoles())
        _res["roles"].append(role);

    _res["expireAt"] = _currentUser.getExpireAt();

    callback(drogon::HttpResponse::newHttpJsonResponse(_res));
}

void V1::AUTHAPI::AuthController::sendMessagesResponse(const std::string &&_typeMessage, const std::string &&_message,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value message;
    message[_typeMessage]= _message;

    auto resp = drogon::HttpResponse::newHttpJsonResponse(message);
    callback(resp);
}


void V1::AUTHAPI::AuthController::sendMessageErrors(const std::string &&_message,
    std::function<void(const drogon::HttpResponsePtr&)>&& callback)
{
    Json::Value message;
    message["error"]= _message;

    auto resp = drogon::HttpResponse::newHttpJsonResponse(message);
    resp->setStatusCode(drogon::k400BadRequest);
    callback(resp);
}
