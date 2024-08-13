cmake_minimum_required(VERSION 3.1...3.29)

if(NOT DEFINED PROJECT_NAME)
  set(PROJECT_NAME "program")
endif(NOT DEFINED PROJECT_NAME)

project(
  ${PROJECT_NAME}
  VERSION 1.0
  LANGUAGES CXX)

string(TIMESTAMP TIME_OF_BUILD "UTC %Y-%m-%d @ %H:%M" UTC)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

message("Source directory: ${CMAKE_SOURCE_DIR}")
message("Target directory: ${CMAKE_CURRENT_BINARY_DIR}")

# temporary, add debug state check later 
# https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html
# ^-- for testing via cmake 
if(DEBUG)
  add_compile_definitions(DEBUG)
  set(WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/")
else()
  add_compile_options(-Werror -O3 -Os -Wall)
  set(WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
endif(DEBUG)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# add_compile_options(-Wall -Wextra -Wpedantic) # SHUT THE FUCK UP

include_directories(${CMAKE_SOURCE_DIR}/inc/)
include_directories(${CMAKE_SOURCE_DIR}/lib/glfw/include/)
include_directories(${CMAKE_SOURCE_DIR}/lib/glad/include/)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

add_compile_options(-DFE_VERSION -DFE_VERSION_TIME="${TIME_OF_BUILD}"
  -DFE_VERSION_MAJOR=${VERSION_MAJOR} 
  -DFE_VERSION_MINOR=${VERSION_MINOR} 
  -DFE_VERSION_PATCH=${VERSION_PATCH})

# NOTE: CMakeLists MUST be reconfigured when new files are added. This is not a
# bug: https://github.com/microsoft/vscode-cmake-tools/issues/722
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)
