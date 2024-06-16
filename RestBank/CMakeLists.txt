cmake_minimum_required(VERSION 3.27 FATAL_ERROR)

set(PROJECT_NAME RestBank)

set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME}
    VERSION 1.0
    LANGUAGES CXX
)

include(FetchContent)
FetchContent_Declare(
    curl
    GIT_REPOSITORY https://github.com/curl/curl.git
    GIT_TAG curl-8_7_1
)

FetchContent_MakeAvailable(curl)

add_executable(${PROJECT_NAME} 
  source/main.cpp 
  source/Rest/RestCurl.cpp)

target_link_libraries(${PROJECT_NAME} libcurl)
