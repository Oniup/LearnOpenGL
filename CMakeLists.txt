cmake_minimum_required(VERSION 3.20)

project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Binaries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Binaries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Binaries)

file(GLOB_RECURSE COMMON_SOURCE_FILES RECURSE ${CMAKE_CURRENT_SOURCE_DIR} "Source/Common/*.cpp")
file(GLOB_RECURSE COMMON_HEADER_FILES RECURSE ${CMAKE_CURRENT_SOURCE_DIR} "Source/Common/*.h")

add_subdirectory(ThirdParty)

function(AddExecutable exec_name)
    add_executable(
        ${exec_name}
            Source/Examples/${exec_name}/${exec_name}.cpp
            ${COMMON_SOURCE_FILES}
            ${COMMON_HEADER_FILES}
    )

    target_compile_definitions(
        ${exec_name}
        PUBLIC
            ${ThirdParty_COMPILE_DEFS}
            EXEC_NAME="${exec_name}"
    )
    target_include_directories(
        ${exec_name}
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/
            ${CMAKE_CURRENT_SOURCE_DIR}/Source/
            ${ThirdParty_INCLUDE_DIRS}
    )
    target_link_libraries(
        ${exec_name}
        PRIVATE
            ${ThirdParty_LIBRARIES}
    )
endfunction()

AddExecutable(1_HelloTriangle)
AddExecutable(2_HelloSquare)
AddExecutable(3_CubeAndBasicLighting)
