cmake_minimum_required(VERSION 3.10)
project(chessGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FetchContent per SFML
include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)

FetchContent_MakeAvailable(SFML)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(chess ${SOURCES})

# Link SFML
target_link_libraries(chess sfml-graphics sfml-window sfml-system)

# Copy project assets (fonts, etc.) into the build directory
set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/assets)
if(EXISTS ${ASSETS_DIR})
    message(STATUS "Copying assets to build directory")
    file(COPY ${ASSETS_DIR} DESTINATION ${CMAKE_BINARY_DIR})
else()
    message(STATUS "No assets directory found at ${ASSETS_DIR}")
endif()

# Copy SFML DLLs to the executable directory (Windows only)
if(WIN32)
    add_custom_command(TARGET chess POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:chess>
        COMMENT "Copying SFML DLLs to executable directory"
    )
    
    # Copy assets to the executable directory
    add_custom_command(TARGET chess POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_BINARY_DIR}/assets
            $<TARGET_FILE_DIR:chess>/assets
        COMMENT "Copying assets to executable directory"
    )
endif()
