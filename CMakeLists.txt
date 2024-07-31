cmake_minimum_required(VERSION 3.20)

project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Binaries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Binaries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Binaries)

file(GLOB_RECURSE COMMON_SOURCE_FILES RECURSE ${CMAKE_CURRENT_SOURCE_DIR} "Source/*.cpp")
file(GLOB_RECURSE COMMON_HEADER_FILES RECURSE ${CMAKE_CURRENT_SOURCE_DIR} "Source/*.h")

function(AddExecutable project_name)
    add_executable(
        ${project_name}
            Main/${project_name}.cpp
            ${COMMON_SOURCE_FILES}
            ${COMMON_HEADER_FILES}
    )

    option(GLFW_BUILD_EXAMPLES OFF)
    option(GLFW_BUILD_TESTS OFF)
    option(GLFW_BUILD_DOCS OFF)
    option(GLFW_INSTALL OFF)

    add_subdirectory(ThirdParty/glad)
    add_subdirectory(ThirdParty/glfw)
    add_subdirectory(ThirdParty/imgui)

    target_compile_definitions(
        ${project_name}
        PUBLIC
            FMT_HEADER_ONLY
    )
    target_include_directories(
        ${project_name}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/
            ${CMAKE_CURRENT_SOURCE_DIR}/Source/
            ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/
            ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glm
            ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/imgui
            ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/fmt/include
            ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glfw/include
            ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/glad/include
    )
    target_link_libraries(
        ${project_name}
        PRIVATE
            imgui glfw glad
    )
endfunction()

AddExecutable(BasicShape)
