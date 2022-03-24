cmake_minimum_required (VERSION 3.14)
project (Branches LANGUAGES CXX)

#please don't build Debug version on windows

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE src_files CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp" "src/*.h")

find_package(Python3 REQUIRED COMPONENTS Interpreter Development NumPy)

if (NOT ${Python3_FOUND})
    message(FATAL_ERROR "Python3.* is not installed. Please install it.")
endif()

if (NOT ${Python3_NumPy_FOUND})
    message(FATAL_ERROR "The \"numpy\" Python3 package is not installed. Please install if using the following command: \"pip3 install numpy\".")
endif()

execute_process(
        COMMAND pip3 show matplotlib
        RESULT_VARIABLE EXIT_CODE
        OUTPUT_QUIET
)

if (NOT ${EXIT_CODE} EQUAL 0)
    message(FATAL_ERROR "The \"matplotlib\" Python3 package is not installed. Please install it using the following command: \"pip3 install matplotlib\".")
endif()

include_directories(${Python3_NumPy_INCLUDE_DIRS})
include_directories(${Python3_INCLUDE_DIRS})
link_libraries(${Python3_LIBRARIES})
link_libraries(Python3::NumPy)

add_executable (Branches ${src_files})