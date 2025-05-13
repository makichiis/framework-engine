cmake_minimum_required(VERSION 3.1...3.29)

set(PROJECT_NAME "framework")

project(
  ${PROJECT_NAME}
  VERSION 1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

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
  add_compile_options(-Werror -O3 -Wall)
  set(WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
endif(DEBUG)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add common include directories
include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/lib/glfw/include/)
include_directories(${CMAKE_SOURCE_DIR}/lib/glad/include/)
include_directories(${CMAKE_SOURCE_DIR}/lib/glm/include/)

# Add the external libraries as subdirectories (assuming CMakeLists.txt exists in these)
add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

# Global compile options
add_compile_options(-DFE_VERSION -DFE_VERSION_TIME="${TIME_OF_BUILD}"
  -DFE_VERSION_MAJOR=${VERSION_MAJOR} 
  -DFE_VERSION_MINOR=${VERSION_MINOR} 
  -DFE_VERSION_PATCH=${VERSION_PATCH})

# Build the shared lib
add_library(${PROJECT_NAME} SHARED 
  src/rootdef.cpp 
  src/object.cpp 
  src/scene_manager.cpp
  src/resource_manager.cpp 
  src/runtime_handler.cpp
  src/assets/shader.cpp
  src/assets/asset.cpp 
  src/render_handler.cpp
  src/assets/basic_color_shader.cpp 
  src/materials/default_material.cpp
  src/renderers/default_renderer.cpp
  src/renderers/renderer.cpp
  src/samples/cube.cpp
)

# Link necessary libraries to the shared library
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)

# -- Tests --

enable_testing()
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test/test_*.cpp")

foreach(test_source ${TEST_SOURCES})
  get_filename_component(test_name ${test_source} NAME_WE)
  
  add_executable(${test_name} ${test_source})
  target_link_libraries(${test_name} PRIVATE ${PROJECT_NAME} glfw)
  
  set_target_properties(${PROJECT_NAME} ${test_name} PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin 
  )

  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

# add_executable(${PROJECT_NAME}_test1
#   test/test_1_library_integrity.cpp  
# )

# add_executable(${PROJECT_NAME}_test2
#   test/test_2_rms.cpp 
# )

# add_executable(${PROJECT_NAME}_test3
#   test/test_3_scene_graph_stress.cpp 
# )

# add_executable(${PROJECT_NAME}_test4
#   test/test_4_renderer_batch.cpp
# )

# add_executable(${PROJECT_NAME}_test5
#   test/test_5_render.cpp
# )

# target_link_libraries(${PROJECT_NAME}_test1 PRIVATE ${PROJECT_NAME} glfw)
# target_link_libraries(${PROJECT_NAME}_test2 PRIVATE ${PROJECT_NAME} glfw)
# target_link_libraries(${PROJECT_NAME}_test3 PRIVATE ${PROJECT_NAME} glfw)
# target_link_libraries(${PROJECT_NAME}_test4 PRIVATE ${PROJECT_NAME} glfw)
# target_link_libraries(${PROJECT_NAME}_test5 PRIVATE ${PROJECT_NAME} glfw)

# set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_test1 PROPERTIES
#   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )

# set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_test2 PROPERTIES
#   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )

# set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_test3 PROPERTIES
#   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )

# set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_test4 PROPERTIES
#   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )

# set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_test5 PROPERTIES
#   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
# )

# add_test(NAME "Library Integrity" COMMAND ${PROJECT_NAME}_test1)
# add_test(NAME "Resource Manager" COMMAND ${PROJECT_NAME}_test2)
# add_test(NAME "Scene Graph Stress Test" COMMAND ${PROJECT_NAME}_test3)
# add_test(NAME "Renderer Batch" COMMAND ${PROJECT_NAME}_test4)
# add_test(NAME "Render" COMMAND ${PROJECT_NAME}_test5)