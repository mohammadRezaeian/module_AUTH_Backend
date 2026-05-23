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

    void validateJsonBody(const Json::Value& _json);

    // bool checkJsonValidation(const RegisterRequest);
};


#endif //AUTH_VALIDATIONSDATAS_H
