#pragma once

#include <spdlog/spdlog.h>
#include <string>

// Minimal logging API for the application.
// - InitLogger() reads config (via extern globals) and creates an async logger
//   according to the configured levels. It registers atexit shutdown so the
//   async thread is stopped automatically.
// - LogMessage(level, text) writes a single log entry with the specified
//   priority and text. Timestamp is included via the logger pattern.

void InitLogger();

// level: spdlog level; text: log message (no formatting).
void Log(spdlog::level::level_enum level, const std::string& text);

