#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "log.h"
#include "parameterLoader.h"
#include "config.h"
#include "Renderor.h"

// --- 1. Define global configuration variables ---
// These can be modified from other files via extern declarations
// Console log level, default is info
spdlog::level::level_enum g_ConsoleLogLevel = spdlog::level::info;
// File log level, recommended default is trace or debug to capture all details
spdlog::level::level_enum g_FileLogLevel = spdlog::level::trace;
// window size: single source of truth
uint32_t WIDTH = 800;
uint32_t HEIGHT = 600;



int main() {
    // Suppose you read config file and modify global variables here
    applyConfig();
    Log::Init();

    Renderor app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // ensure logs are flushed and async threads stopped
    Log::Shutdown();

    return EXIT_SUCCESS;
}
