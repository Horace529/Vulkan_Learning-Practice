#pragma once

#include <spdlog/spdlog.h>
#include <utility>

// Lightweight wrapper class around spdlog. All methods are static so callers
// can call Log::Init() / Log::Debug(...) etc. without instantiating.
class Log {
public:
    // initialize logging (implemented in log.cpp)
    static void Init();
    static void Shutdown();

   // No changes made to the methods

    static bool ShouldLog(spdlog::level::level_enum level) { return spdlog::should_log(level); }

    template<typename... Args>
    static inline void Trace(const char* fmt, Args&&... args) {
        if (spdlog::should_log(spdlog::level::trace)) spdlog::trace(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static inline void Debug(const char* fmt, Args&&... args) {
        if (spdlog::should_log(spdlog::level::debug)) spdlog::debug(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static inline void Info(const char* fmt, Args&&... args) {
        if (spdlog::should_log(spdlog::level::info)) spdlog::info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static inline void Warn(const char* fmt, Args&&... args) {
        if (spdlog::should_log(spdlog::level::warn)) spdlog::warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static inline void Error(const char* fmt, Args&&... args) {
        if (spdlog::should_log(spdlog::level::err)) spdlog::error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static inline void Critical(const char* fmt, Args&&... args) {
        if (spdlog::should_log(spdlog::level::critical)) spdlog::critical(fmt, std::forward<Args>(args)...);
    }
};
