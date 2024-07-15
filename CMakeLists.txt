cmake_minimum_required(VERSION 3.15)
project(lawena-ng)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_options(/Wall /O2)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
    add_compile_options(-march=native -O2 -Wall -Wextra -Wpedantic)
    add_link_options(-march=native -O2 -Wall -Wextra -Wpedantic)
    
    # alpine doesn't support libsanitizer
    cmake_host_system_information(RESULT DISTRO_ID QUERY DISTRIB_PRETTY_NAME)
    if (DISTRO_ID MATCHES "^Alpine")
        # NOP
    else()
        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)
    endif()
endif()

add_executable(${PROJECT_NAME} "src/Lawena.cpp" "src/SettingsManager.cpp" "src/CommandLine.cpp" "src/CLWindows.cpp")
