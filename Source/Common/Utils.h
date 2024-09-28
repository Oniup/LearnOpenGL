#pragma once

#include <cinttypes>
#include <limits>
#include <string>
#include <string_view>

constexpr uint32_t InvalidId = std::numeric_limits<uint32_t>::max();

std::string ReadSource(const std::string_view& shader_path);
