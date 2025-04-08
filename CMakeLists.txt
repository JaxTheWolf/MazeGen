cmake_minimum_required(VERSION 3.30)
project(MazeGen)

add_executable(${PROJECT_NAME} main.cpp
        Cell.hpp
        functions.cpp
        functions.hpp
)

# Tell CMake we want to use C++17 and not to include language extensions
set_target_properties(${PROJECT_NAME}
  PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Set compile flags that span across all source files
target_compile_options(${PROJECT_NAME}
        PRIVATE
        -Wall
        -Wextra
        -Werror=shadow
        -Wpedantic
        -pedantic
)