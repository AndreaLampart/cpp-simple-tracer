#pragma once

// pid, tid includes
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

// timer includes
#include <chrono>
#include <cstdlib>

// proc name includes
#include <string>

// file includes
#include <filesystem>
#include <fstream>
#include <mutex>
#include <nlohmann/json.hpp>

namespace cpp_tracing {

class ScopedTracer {
   public:
    ScopedTracer(const std::string& proc_name)
        : proc_name_(proc_name), start_(std::chrono::high_resolution_clock::now()) {}
    ~ScopedTracer() {
        auto end = std::chrono::high_resolution_clock::now();
        using json = nlohmann::json;

        std::lock_guard<std::mutex> guard(file_access_mutex_);
        json trace_file;
        if (std::filesystem::exists("trace.json")) {
            std::ifstream ifs("trace.json");
            ifs >> trace_file;
        } else {
            trace_file["traceEvents"] = {};
        }

        json trace;
        trace["pid"] = getpid();
        trace["tid"] = syscall(SYS_gettid);
        trace["ts"] = std::chrono::time_point_cast<std::chrono::microseconds>(start_)
                          .time_since_epoch()
                          .count();
        trace["dur"] = std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
        trace["ph"] = "X";
        trace["name"] = proc_name_;
        trace["args"]["us"] =
            std::chrono::duration_cast<std::chrono::microseconds>(end - start_).count();
        trace_file["traceEvents"].push_back(trace);
        std::ofstream ofs("trace.json");
        ofs << trace_file << std::endl;
    }

   private:
    std::mutex file_access_mutex_;
    std::string proc_name_;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
};

}  // namespace cpp_tracing
