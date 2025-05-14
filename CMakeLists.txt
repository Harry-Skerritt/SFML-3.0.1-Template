cmake_minimum_required(VERSION 3.16)
project(SFMLProject)

# Set the output directories for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# windows specific configurations
if(WIN32)
    set(CMAKE_CXX_FLAGS "-static-libgcc -static-libstdc++")
    set(CMAKE_EXE_LINKER_FLAGS "-static")
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
endif()

# macOS specific configurations
if(APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET 15.4)
    set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

#---- Fetch SFML 3 ----#
include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG master
)

FetchContent_MakeAvailable(SFML)

# Set up source files
set(SOURCE_FILES
        src/main.cpp
        src/Game.cpp
        src/Game.h
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Link SFML 3 libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
        SFML::Network
)

# macOS-specific frameworks and bundle setup
if(APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    find_library(COREFOUNDATION_LIBRARY CoreFoundation REQUIRED)

    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
            ${COCOA_LIBRARY}
            ${IOKIT_LIBRARY}
            ${COREVIDEO_LIBRARY}
            ${COREFOUNDATION_LIBRARY}
    )

    set(MACOSX_BUNDLE TRUE)

    set(APP_ICON "${CMAKE_SOURCE_DIR}/mac/icon.icns")
    set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${APP_ICON})

    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_BUNDLE_NAME "${CMAKE_PROJECT_NAME}"
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/mac/Info.plist"
    )

    # Copy Data folder into .app bundle
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Data"
            "$<TARGET_BUNDLE_CONTENT_DIR:${CMAKE_PROJECT_NAME}>/Resources/Data"
            COMMENT "Copying Data/ into app bundle Resources..."
    )
else()
    # Copy Data next to executable on Windows/Linux
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/Data"
            "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Data"
            COMMENT "Copying Data/ next to executable..."
    )
endif()

