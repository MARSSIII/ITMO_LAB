cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(PROJECT_NAME CubikRubik)

set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME})


add_executable(${PROJECT_NAME}
  source/main.cpp
  source/Window/window.cpp
  source/Window/WindowEvents.cpp
  source/Camera/Camera.cpp
  source/graphics/Shader.cpp
  source/Figure/Cube.cpp
  source/Figure/Cubes.cpp
)


find_package(glm REQUIRED)
if(glm_FOUND)
  target_link_libraries(${PROJECT_NAME} PRIVATE glm)
else()
  message(FATAL_ERROR "glm library not found")
endif()


find_package(glfw3 3.4 REQUIRED)
if(glfw3_FOUND)
  target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
else()
  message(FATAL_ERROR "glfw3 library not found")
endif()


find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
  target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
else()
  message(FATAL_ERROR "OpenGL library not found")
endif()


find_package(GLEW REQUIRED)
if(GLEW_FOUND)
  target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
else()
  message(FATAL_ERROR "GLEW library not found")
endif()

