cmake_minimum_required(VERSION 3.5)

include(FetchContent)

project(Auth CXX)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cc
        models/User.cpp
        models/User.h
        dto/AuthResponse.cpp
        dto/AuthResponse.h
        password/PasswordHasher.cpp
        password/PasswordHasher.h
        repository/UserRepository.cpp
        repository/UserRepository.h
        services/AuthService.cpp
        services/AuthService.h
        dto/RegisterRequest.cpp
        dto/RegisterRequest.h
        controllers/AuthController.h
        controllers/AuthController.cc
        dto/LoginRequest.cpp
        dto/LoginRequest.h
        filters/JwtAuthFilter.cpp
        filters/JwtAuthFilter.h
        services/JwtService.cpp
        services/JwtService.h
        models/CurrentUser.cpp
        models/CurrentUser.h
        services/ValidationsDatas.cpp
        services/ValidationsDatas.h)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# add_subdirectory(drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
#FetchContent_Declare(
#        yaml-cpp
#        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
#        GIT_TAG master
#)
#
#FetchContent_MakeAvailable(yaml-cpp)
set(JWT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(JWT_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
        jwt-cpp
        GIT_REPOSITORY https://github.com/Thalhammer/jwt-cpp.git
        GIT_TAG v0.7.2
)
FetchContent_MakeAvailable(jwt-cpp)

find_package(yaml-cpp REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(nlohmann_json REQUIRED )
find_package(Drogon CONFIG REQUIRED)
find_library(ARGON2_LIB argon2 REQUIRED)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        yaml-cpp
        Drogon::Drogon
        jwt-cpp::jwt-cpp
        OpenSSL::SSL
        OpenSSL::Crypto
        nlohmann_json::nlohmann_json
        ${ARGON2_LIB}
)

# ##############################################################################

if (CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "c++17 or higher is required")
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20")
endif ()

#aux_source_directory(controllers CTL_SRC)
##aux_source_directory(routes ROUTES_SRC)
#
#aux_source_directory(services SERVICES_SRC)
#aux_source_directory(repository REPOSITORY_SRC)
#aux_source_directory(filters FILTER_SRC)
#aux_source_directory(dto DTO_SRC)
#aux_source_directory(models MODEL_SRC)
#aux_source_directory(jwt JWT_SRC)
#aux_source_directory(password PASSWORD_SRC)
#aux_source_directory(utils UTILS_SRC)
#
#aux_source_directory(plugins PLUGIN_SRC)


drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME}
                           PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${SERVICES_SRC}
               ${REPOSITORY_SRC}
               ${FILTER_SRC}
               ${DTO_SRC}
               ${MODEL_SRC}
               ${JWT_SRC}
               ${PASSWORD_SRC}
               ${UTILS_SRC}
               ${PLUGIN_SRC}
)


# ##############################################################################
# uncomment the following line for dynamically loading views 
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)
#set(DRAGON_USE_YAMLCPP ON)
# ##############################################################################

add_subdirectory(test)
