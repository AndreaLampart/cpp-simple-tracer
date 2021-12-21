cmake_minimum_required(VERSION 2.8.11)
project(cpp_trace)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_FLAGS "-pthread -Wall -Werror -Wpedantic -march=native")

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
find_package(nlohmann_json REQUIRED)

add_subdirectory(lib)
add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME}
PRIVATE
  cpp_tracing_lib
)
