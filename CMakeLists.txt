cmake_minimum_required(VERSION 3.19)

project(lawena-ng LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    src/Logger.cpp
    src/Logger.hpp
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.hpp
    src/SettingsManager.cpp
    src/SettingsManager.hpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt::Core
    Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if (UNIX)
    # Install the .desktop file
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/desktop/lawena-ng.desktop
        DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
    )
    
    # Install the icon file    
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/data/icons/lawena-ng.ico
        DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/256x256/apps/
    )
endif()

# Enable compiler warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Link-Time Optimizations (only for Release builds)
option(WITH_LTO "Enable Link-Time Optimization" OFF)
if (WITH_ASAN)
    if (MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /LTCG)
        target_link_options(${PROJECT_NAME} PRIVATE /LTCG)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -flto)
        target_link_options(${PROJECT_NAME} PRIVATE -flto)
    endif()
endif()

# AddressSanitizer
option(WITH_ASAN "Enable AddressSanitizer" OFF)
if (WITH_ASAN)
    if (MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /fsanitize=address)
        target_link_options(${PROJECT_NAME} PRIVATE /fsanitize=address)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
        target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
    endif()
endif()

# UndefinedBehaviorSanitizer
option(WITH_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)
if (WITH_UBSAN)
    if (MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE /fsanitize=undefined)
        target_link_options(${PROJECT_NAME} PRIVATE /fsanitize=undefined)
    else()
        target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=undefined)
        target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=undefined)
    endif()
endif()

# UPX
option(WITH_UPX "Enable Ultimate Packer for eXecutables" OFF)
if (WITH_UPX)
    find_program(UPX_PATH upx)
    if (UPX_PATH)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND upx --best --lzma $<TARGET_FILE:${PROJECT_NAME}>
            COMMENT "Compressing executable with UPX")
    else()
        message(WARNING "UPX not found. Are you sure it's in PATH? Skipping compression.")
    endif()
endif()