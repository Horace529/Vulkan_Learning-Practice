#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <spdlog/spdlog.h>
#include "config.h"


// --- 1. loading configs ---
std::unordered_map<std::string, std::string> loadConfig(const std::string& filename) {
    std::unordered_map<std::string, std::string> config;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "WARNING, NO CONFIG FILE FOUND " << filename << "USING DEFAULT CONFIG\n";
        return config;
    }

    std::string line;
    while (std::getline(file, line)) {
        // 跳过空行和注释
        if (line.empty() || line[0] == '#') continue;

        // 寻找等号的位置
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            config[key] = value;
        }
    }
    return config;
}

// --- 2. 应用配置 ---
void applyConfig() {
    auto config = loadConfig("config");

    // 如果配置文件里有对应的键，就提取并转换
    if (config.count("ConsoleLogLevel")) {
        // spdlog 提供现成的 from_str，完美对接文本配置
        g_ConsoleLogLevel = spdlog::level::from_str(config["ConsoleLogLevel"]);
    }

    if (config.count("FileLogLevel")) {
        g_FileLogLevel = spdlog::level::from_str(config["FileLogLevel"]);
    }

    if (config.count("WindowWidth")) {
        // 字符串转整数用 std::stoi
        WIDTH = static_cast<uint32_t>(std::stoi(config["WindowWidth"]));
    }

    if (config.count("WindowHeight")) {
        HEIGHT = static_cast<uint32_t>(std::stoi(config["WindowHeight"]));
    }
}
