cmake_minimum_required(VERSION 3.1...3.29)

project(
  glad
  VERSION 2.0
  LANGUAGES C
)

add_library(glad "include/glad/gl.h" "include/KHR/khrplatform.h" "src/gl.c")
target_include_directories(glad PUBLIC "include/")

