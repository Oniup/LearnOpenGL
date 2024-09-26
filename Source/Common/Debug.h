#pragma once

#include <fmt/color.h>
#include <fmt/format.h>

#ifdef _MSC_VER
#    define INTERNAL_GENERATE_TRAP() __debugbreak()
#else
#    define INTERNAL_GENERATE_TRAP() __builtin_trap()
#endif

#define ASCII_RED "\033[31m"
#define ASCII_RESET "\033[0m"

#define ASSERT(_Expression, ...)                                                                  \
    if (!(_Expression)) {                                                                         \
        fmt::print(stderr, fmt::emphasis::bold,                                                   \
                   ASCII_RED "Assert ({}) == false: '{}' {}{}:\n{}\n" ASCII_RESET, #_Expression,  \
                   __FILE__, __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__));                   \
        INTERNAL_GENERATE_TRAP();                                                                 \
    }                                                                                             \
    else                                                                                          \
        ((void)0)

#define ERROR(...)                                                                                \
    fmt::print(stderr, ASCII_RED "Error: '{}' {}{}:\n{}\n" ASCII_RESET, __FILE__, __FUNCTION__,   \
               __LINE__, fmt::format(__VA_ARGS__))

#define FATAL(...)                                                                                \
    fmt::print(stderr, fmt::emphasis::bold, ASCII_RED "Fatal: '{}' {}{}:\n{}\n" ASCII_RESET,      \
               __FILE__, __FUNCTION__, __LINE__, fmt::format(__VA_ARGS__));                       \
    INTERNAL_GENERATE_TRAP()

#define LOG(...)                                                                                  \
    fmt::print(stdout, "Message: '{}' {}{}:\n{}\n", __FILE__, __FUNCTION__, __LINE__,             \
               fmt::format(__VA_ARGS__))
