cmake_minimum_required(VERSION 3.1...3.29)

project(
  FrameworkCore
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

string(TIMESTAMP TIME_OF_BUILD "UTC %Y-%m-%d @ %H:%M" UTC)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

message("Source directory: ${CMAKE_SOURCE_DIR}")
message("Target directory: ${CMAKE_CURRENT_BINARY_DIR}")

message("${CMAKE_BUILD_TYPE}")

# https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html
if(DEFINED CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
  message("Setting debug configurations...")
  add_compile_definitions(DEBUG)
  add_compile_options(-Werror -Wall -g -O1 -fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-g -fsanitize=address,undefined)
  set(WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/")
else()
  message("Setting release configurations...")
  add_compile_options(-Werror -Wall -O3)
  set(WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the external libraries as subdirectories (assuming CMakeLists.txt exists in these)
# TODO: Isolate GLAD to unified GL header when level editor refactor is done
add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

add_compile_options(-DFE_VERSION -DFE_VERSION_TIME="${TIME_OF_BUILD}"
  -DFE_VERSION_MAJOR=${VERSION_MAJOR} 
  -DFE_VERSION_MINOR=${VERSION_MINOR} 
  -DFE_VERSION_PATCH=${VERSION_PATCH})

# For ease-of-reading, keep these listed in lexiographical order (as they appear in a file tree)
add_library(FrameworkCore STATIC 

  src/assets/asset.cpp 
  src/assets/basic_color_shader.cpp 
  src/assets/shader.cpp

  src/interface/window.cpp

  src/materials/default_material.cpp

  src/meshes/mesh.cpp

  src/renderers/default_renderer.cpp
  src/renderers/renderer.cpp

  src/samples/cube.cpp

  src/scene_objects/camera.cpp
  src/scene_objects/scene.cpp

  src/object.cpp
  src/render_handler.cpp
  src/resource_manager.cpp 
  src/rootdef.cpp 
  src/runtime_handler.cpp
  src/scene_manager.cpp

)

target_include_directories(FrameworkCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(FrameworkCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include/)
target_include_directories(FrameworkCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/include/)
target_include_directories(FrameworkCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib/glm/include/) 

target_link_libraries(FrameworkCore PRIVATE glfw glad)

# -- Tests --

enable_testing()
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test/test_*.cpp")

foreach(test_source ${TEST_SOURCES})
 get_filename_component(test_name ${test_source} NAME_WE)
 
 add_executable(${test_name} ${test_source})
 target_link_libraries(${test_name} INTERFACE "-E" PUBLIC FrameworkCore)
 
 set_target_properties(FrameworkCore ${test_name} PROPERTIES 
   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib 
   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin 
 )

 add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
