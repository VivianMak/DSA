#!/usr/bin/env bash
#
# build_ws - scaffolds a new C++ project with the standard
#            src/, include/, build/, tests/ layout.
#
# Usage:
#   ./build_ws <folder_path>
#
# Example:
#   ./build_ws ~/DSA/Assignment2/NewProject

set -euo pipefail

# --- Argument validation ---
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <folder_path>" >&2
    exit 1
fi

PROJECT_PATH="$1"
PROJECT_NAME="$(basename "$PROJECT_PATH")"

if [ -e "$PROJECT_PATH" ]; then
    echo "Error: '$PROJECT_PATH' already exists. Choose a new path or remove it first." >&2
    exit 1
fi

# --- Create directory structure ---
mkdir -p "$PROJECT_PATH"/{src,include,build,tests}

echo "Created folder structure under $PROJECT_PATH:"
echo "  src/"
echo "  include/"
echo "  build/"
echo "  tests/"

# --- Root CMakeLists.txt ---
cat > "$PROJECT_PATH/CMakeLists.txt" << EOF
cmake_minimum_required(VERSION 3.10)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

##### Build Libraries #####

# Add one add_library() block per module, e.g.:
# add_library(mymodule
#     src/mymodule.cpp
# )
# target_include_directories(mymodule PUBLIC include)
# target_link_libraries(mymodule PUBLIC Eigen3::Eigen)

enable_testing()
add_subdirectory(tests)

# Main program executable
add_executable(main src/main.cpp)
target_link_libraries(main
    # link your libraries here, e.g.: mymodule
)
EOF

echo "Created CMakeLists.txt"

# --- tests/CMakeLists.txt ---
cat > "$PROJECT_PATH/tests/CMakeLists.txt" << 'EOF'
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
    # add your test .cpp files here, e.g.: test_mymodule.cpp
)

target_link_libraries(unit_tests PRIVATE
    # link the libraries under test here, e.g.: mymodule
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
EOF

echo "Created tests/CMakeLists.txt"

# --- Minimal starter main.cpp so the project builds out of the box ---
cat > "$PROJECT_PATH/src/main.cpp" << 'EOF'
#include <iostream>

int main()
{
    std::cout << "Hello from the new project!" << std::endl;
    return 0;
}
EOF
