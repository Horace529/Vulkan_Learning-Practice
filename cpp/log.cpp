#include <iostream>
#include <vector>
#include <algorithm> // for std::min
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/async_logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <filesystem>
#include <chrono>
#include "config.h"
#include "log.h"

// Initialize logger, use global configuration variables
void Log::Init() {
    try {
        // ensure logs directory exists
        std::filesystem::create_directories("logs");

        // init async thread pool: queue size 8192, 1 worker thread
        spdlog::init_thread_pool(8192, 1);

        // 1. Console sink: use the global console log level
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(g_ConsoleLogLevel);

        // 2. File sink: use the global file log level
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/engine.log", true);
        file_sink->set_level(g_FileLogLevel);

        // 3. Combine sinks and create async logger
        std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };

        auto async_logger = std::make_shared<spdlog::async_logger>(
            "Engine", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        async_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");

        spdlog::register_logger(async_logger);
        spdlog::set_default_logger(async_logger);

        // global level
        spdlog::set_level(spdlog::level::trace);

        // periodically flush every 3 seconds
        spdlog::flush_every(std::chrono::seconds(3));

        spdlog::info("Async log initialized. ConsoleLevel={}, FileLevel={}",
            spdlog::level::to_string_view(g_ConsoleLogLevel),
            spdlog::level::to_string_view(g_FileLogLevel));
    }
    catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}

void Log::Shutdown() {
    spdlog::shutdown();
}
