cmake_minimum_required(VERSION 3.15)
project(lawena-ng)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)

if (MSVC)
    add_compile_options(/Wall)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address)
    add_link_options(-Wall -Wextra -Wpedantic -fsanitize=address)
endif()

add_executable(${PROJECT_NAME} "src/Lawena.cpp" "src/SettingsManager.cpp")
