cmake_minimum_required (VERSION 3.12)
project (Branches LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE src_files CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp" "src/*.h")

find_package(Python3 REQUIRED COMPONENTS Interpreter Development NumPy)
include_directories(${Python3_INCLUDE_DIRS})
link_libraries(${Python3_LIBRARIES})

add_executable (Branches ${src_files})