#ifndef AUTH_VALIDATIONSDATAS_H
#define AUTH_VALIDATIONSDATAS_H
#include <string>
#include "dto/RegisterRequest.h"
#include  "dto/LoginRequest.h"
#include "dto/AuthResponse.h"

class ValidationsDatas
{
private:

public:
    template <typename T>
    void validateJson(const T& _json);

    void validateJsonBody(const std::shared_ptr<Json::Value> _json);
    void validateJsonBodyLogin(const std::shared_ptr<Json::Value> _json);

};


#endif //AUTH_VALIDATIONSDATAS_H
