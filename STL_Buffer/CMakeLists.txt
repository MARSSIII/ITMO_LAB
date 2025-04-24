cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(PROJECT_NAME CircularBuffer)

project(${PROJECT_NAME}
        LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  source/main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer
        ${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer/Iterator
)
