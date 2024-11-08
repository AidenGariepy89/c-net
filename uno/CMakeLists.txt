cmake_minimum_required(VERSION 3.22.0)

project(uno)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use stricter compiler warnings
if (MSVC)
    # Microsoft Visual C++
    add_compile_options(/EHsc /W4) 
else()
    # GCC and Clang
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ncurses)
target_include_directories(${PROJECT_NAME} PUBLIC src)
