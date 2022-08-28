cmake_minimum_required(VERSION 3.19)
project(engine)

set(CMAKE_CXX_STANDARD 20)

CPMAddPackage(
        NAME spdlog
        GITHUB_REPOSITORY gabime/spdlog
        GIT_TAG v1.10.0
        EXCLUDE_FROM_ALL YES
)

CPMAddPackage(
        NAME GLEW
        GITHUB_REPOSITORY Perlmint/glew-cmake
        GIT_TAG glew-cmake-2.2.0
        EXCLUDE_FROM_ALL YES
        OPTIONS
        "ONLY_LIBS ON"
        "glew-cmake_BUILD_SHARED OFF"
        "glew-cmake_BUILD_STATIC ON"
)

CPMAddPackage(
        NAME glfw
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG master # new cursor shapes only available in master TODO: change this
        EXCLUDE_FROM_ALL YES
        OPTIONS
        "BUILD_SHARED_LIBS OFF"
        "GLFW_INSTALL OFF"
        "GLFW_BUILD_TESTS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_DOCS OFF"
)

CPMAddPackage(
        NAME glm
        GITHUB_REPOSITORY g-truc/glm
        GIT_TAG 0.9.9.8
        EXCLUDE_FROM_ALL YES
)

CPMAddPackage(
        NAME EnTT
        GITHUB_REPOSITORY skypjack/entt
        GIT_TAG v3.10.1
)

CPMAddPackage(
        NAME stb
        GITHUB_REPOSITORY gracicot/stb-cmake
        GIT_TAG master
        OPTIONS
        "STB_EXPORT OFF"
        "STB_INSTALL OFF"
)

CPMAddPackage(
        NAME tinygltf
        GITHUB_REPOSITORY syoyo/tinygltf
        GIT_TAG master
        OPTIONS
        "TINYGLTF_HEADER_ONLY OFF"
        "TINYGLTF_INSTALL OFF"
        "TINYGLTF_BUILD_TESTS OFF"
        "TINYGLTF_BUILD_EXAMPLES OFF"
        "TINYGLTF_BUILD_LOADER_EXAMPLE OFF"
)

CPMAddPackage(
        NAME magic_enum
        GITHUB_REPOSITORY Neargye/magic_enum
        GIT_TAG v0.8.1
)

file(
        GLOB_RECURSE SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(
        ${PROJECT_NAME}
        spdlog
        libglew_static
        glfw
        glm
        EnTT
        stb::image
        tinyobjloader
        magic_enum
)

target_precompile_headers(${PROJECT_NAME} PUBLIC
        <memory>
        <algorithm>
        <functional>
        <fstream>
        <iostream>
        <sstream>
        <string>
        <vector>
        <array>
        <unordered_map>
        <set>
        <limits>
        )