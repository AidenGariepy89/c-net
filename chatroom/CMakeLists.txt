cmake_minimum_required(VERSION 3.22.0)

project(chat)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

file(GLOB_RECURSE SOURCES "src/*.c")

include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCES})
