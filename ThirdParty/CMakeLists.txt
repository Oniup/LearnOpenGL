option(BUILD_SHARED_LIBS ON)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(imgui)

set(ThirdParty_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/fmt/include
    ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/glad/include
CACHE INTERNAL "")

set(ThirdParty_LIBRARIES
    imgui glfw glad
CACHE INTERNAL "")

set(ThirdParty_COMPILE_DEFS
    GLFW_DLL
    FMT_HEADER_ONLY
    STB_IMAGE_IMPLEMENTATION
CACHE INTERNAL "")
