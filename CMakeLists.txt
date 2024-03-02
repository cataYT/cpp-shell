cmake_minimum_required(VERSION 3.0)

project(cpp_shell)

# Find libcurl package
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

# Add executable target
add_executable(cpp_shell main.cpp functions.hpp randomimg.hpp)

# Set compiler optimization flags
target_compile_options(cpp_shell PRIVATE -O3)

# Link against libcurl
target_link_libraries(cpp_shell ${CURL_LIBRARIES})
