#pragma once

#include <fmt/color.h>
#include <fmt/format.h>

#ifdef _MSC_VER
#    define INTERNAL_GENERATE_TRAP() __debugbreak()
#else
#    define INTERNAL_GENERATE_TRAP() __builtin_trap()
#endif

#define Assert(_Expression, ...)                                                                  \
    if (!(_Expression)) {                                                                         \
        fmt::print(stderr, fmt::emphasis::bold | fmt::fg(fmt::color::red),                        \
                   "Assert ({}) == false: '{}' {}{}:\n{}\n", #_Expression, __FILE__,              \
                   __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__));                             \
        INTERNAL_GENERATE_TRAP();                                                                 \
    } else                                                                                        \
        ((void)0)

#define Error(...)                                                                                \
    fmt::print(stderr, fmt::fg(fmt::color::red), "Error: '{}' {}{}:\n{}\n", __FILE__,             \
               __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__))

#define Message(...)                                                                              \
    fmt::print(stdout, "Message: '{}' {}{}:\n{}\n", __FILE__, __FUNCTION__, __LINE__,             \
               fmt::format(__VA_ARGS__))
