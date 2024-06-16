cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(PROJECT_NAME IntegerSet)

set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME}
  LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
  source/main.cpp
  source/Menu/Menu.cpp
  source/IntegerSet/IntegerSet.cpp  
)


