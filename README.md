# CPP Scoped Tracer
 ![trace_screenshot](/res/trace.png)
Simple example on how to implement a quick and dirty scoped tracer for your private C++ project.

## Building the test
For simplicity, this project uses the conan package manager for the dependencies. Feel free to use something else.
### Conan
```pip install conan```
### Build
```mkdir build && cd build && cmake .. && make -j```

## How to use
Copy the contents of ./lib into your project folder. Make sure you have nlohmann-json installed or provide it using conan. Then add something like this:

CMakeLists.txt:
```
find_package(nlohmann_json REQUIRED)

add_subdirectory(lib)
add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME}
PRIVATE
  cpp_tracing_lib
)
```

To generate a trace, just add a ScopedTracer to the scope you want to trace:
```
cpp_tracing::ScopedTracer trace("my_trace");
```

This will generate a trace.json file in your build folder. Open a chrome browser window with url  ```chrome://tracing/``` and drag and drop trace.json there. 
