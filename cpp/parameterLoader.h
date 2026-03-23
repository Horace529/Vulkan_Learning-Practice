#pragma once

#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> loadConfig(const std::string& filename);
void applyConfig();
