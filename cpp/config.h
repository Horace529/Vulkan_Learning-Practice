#pragma once

#include <spdlog/spdlog.h>
#include <cstdint>

// Declarations of configuration globals used across translation units
extern spdlog::level::level_enum g_ConsoleLogLevel;
extern spdlog::level::level_enum g_FileLogLevel;
// Use WIDTH/HEIGHT as the single source of truth for window size
extern uint32_t WIDTH;
extern uint32_t HEIGHT;
