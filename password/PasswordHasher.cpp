//
// Created by root on 5/20/26.
//

#include "PasswordHasher.h"

#include <argon2.h>

#include <random>
#include <sstream>
#include <stdexcept>
#include <vector>


namespace {

    constexpr uint32_t t_cost = 3;
    constexpr uint32_t m_cost = 1 << 16;
    constexpr uint32_t parallelism = 1;
    constexpr uint32_t salt_length = 16;
    constexpr uint32_t hash_length = 32;

    std::vector<uint8_t> generateSalt()
    {
        std::vector<uint8_t> salt(salt_length);

        std::random_device rd;

        for (auto& b : salt)
        {
            b = static_cast<uint8_t>(rd());
        }

        return salt;
    }

}

std::string PasswordHasher::hash(
    const std::string& password
) {

    auto salt = generateSalt();
    size_t encoded_len = argon2_encodedlen(
        t_cost,
        m_cost,
        parallelism,
        salt.size(),
        hash_length,
        Argon2_id
    );

    std::vector<char> encoded(encoded_len);

    int result = argon2id_hash_encoded(
        t_cost,
        m_cost,
        parallelism,
        password.c_str(),
        password.size(),
        salt.data(),
        salt.size(),
        hash_length,
        encoded.data(),
        encoded.size()
    );

    if (result != ARGON2_OK) {
        throw std::runtime_error(
            "argon2 hash failed"
        );
    }

    return std::string(encoded.data());
}

bool PasswordHasher::verify(
    const std::string& password,
    const std::string& hash
) {

    return argon2id_verify(hash.c_str(),password.c_str(),password.size()) == ARGON2_OK;
}