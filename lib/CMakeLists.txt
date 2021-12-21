set(LIBNAME cpp_tracing_lib)
find_package(nlohmann_json REQUIRED)

add_library(${LIBNAME} INTERFACE)

target_include_directories(${LIBNAME}
INTERFACE
    include
)

target_link_libraries(${LIBNAME}
INTERFACE
    nlohmann_json::nlohmann_json
)
