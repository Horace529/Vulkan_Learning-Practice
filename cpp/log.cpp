#include <iostream>
#include <vector>
#include <algorithm> // for std::min
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "config.h"

// Initialize logger, use global configuration variables
void initLogger() {
    try {
        // 1. Console sink: use the global console log level
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(g_ConsoleLogLevel);

        // 2. File sink: use the global file log level
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("/logs/engine.log", true);
        file_sink->set_level(g_FileLogLevel);

        // 3. Combine sinks
        std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
        auto logger = std::make_shared<spdlog::logger>("Engine", sinks.begin(), sinks.end());
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] %v");

        // 4. Set as default logger
        spdlog::set_default_logger(logger);

        // [Important] Set global base level
        // Must be set to the lowest level (trace), otherwise file sink won't receive trace logs
        spdlog::set_level(spdlog::level::trace);

        // Print a startup message confirming current levels
        spdlog::info("Log system initialized successfully! Current console output level: {}",
            spdlog::level::to_string_view(g_ConsoleLogLevel));

    }
    catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log initialization failed: " << ex.what() << std::endl;
    }
}
