#include <thread>
#include "cpp_tracing.h"

int main(int argc, char const* argv[]) {
    cpp_tracing::ScopedTracer tracer("main");
    
    const auto foo = [](){
        cpp_tracing::ScopedTracer trace_foo("foo");
        sleep(1);
        return;
    };
    const auto bar = [](){
        cpp_tracing::ScopedTracer trace_bar("bar");
        sleep(2);
        return;
    };
    const auto gore = [](){
        cpp_tracing::ScopedTracer trace_gore("gore");
        sleep(3);
        return;
    };
    
    std::thread thread_0(foo);
    std::thread thread_1(bar);
    std::thread thread_2(gore);

    thread_0.join();
    thread_1.join();
    thread_2.join();
    return 0;
}
