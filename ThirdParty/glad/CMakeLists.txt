project(
    glad
    LANGUAGES C
)

add_library(
    glad SHARED
        include/glad/glad.h
        include/KHR/khrplatform.h
        src/glad.c
)

target_include_directories(
    glad
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
