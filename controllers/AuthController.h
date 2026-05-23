#ifndef AUTH_AUTHCONTROLLER_H
#define AUTH_AUTHCONTROLLER_H

#include <drogon/HttpController.h>
#include  "dto/LoginRequest.h"

#include "dto/RegisterRequest.h"
#include "services/AuthService.h"
#include "services/ValidationsDatas.h"

#include <json/json.h>
#include <models/CurrentUser.h>


namespace V1
{
    namespace AUTHAPI
    {
        class AuthController : public drogon::HttpController<AuthController>
        {
        private:
            RegisterRequest  m_registerRequest;
            AuthService      m_authService;
            ValidationsDatas m_validationsDatas;

            void sendMessagesResponse(const std::string &&_typeMessage, const std::string &&_message, std::function<void(const drogon::HttpResponsePtr&)>&& callback);
            void sendMessageErrors(const std::string &&_message, std::function<void(const drogon::HttpResponsePtr&)>&& callback);

        public:

            METHOD_LIST_BEGIN

            METHOD_ADD(AuthController::registerUser, "/auth/register", drogon::Post);
            METHOD_ADD(AuthController::loginUser, "/auth/login", drogon::Post);
            METHOD_ADD(AuthController::me, "/auth/me", drogon::Get, "JwtAuthFilter");

            METHOD_LIST_END

            void registerUser(const drogon::HttpRequestPtr& req,std::function<void(const drogon::HttpResponsePtr&)>&& callback);
            void loginUser(const drogon::HttpRequestPtr& req,std::function<void(const drogon::HttpResponsePtr&)>&& callback);
            void me(const drogon::HttpRequestPtr& req,std::function<void(const drogon::HttpResponsePtr&)>&& callback);

        };
    }
}


#endif //AUTH_AUTHCONTROLLER_H
