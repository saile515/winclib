cmake_minimum_required(VERSION 3.25)

project(
  "winclib"
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(winclib STATIC src/window.cpp src/window_manager.cpp)
