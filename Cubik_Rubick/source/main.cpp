#include "Camera/Camera.hpp"
#include "Figure/Cube.hpp"
#include "Figure/Cubes.hpp"
#include "Window/WindowEvents.hpp"
#include "Window/window.hpp"
#include "graphics/Shader.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#define log(x) std::cerr << x << std::endl

int WindowSizeX = 1000;
int WindowSizeY = 800;

int main() {

  if (!Window::initialize(WindowSizeX, WindowSizeY, "Cubik Rubik")) {
    log("Error init Window");
    return 1;
  }

  Events::initialize();

  Shader *CubeShaderProgram = LoadShader("../ShaderFile/CubeShader.glslv",
                                         "../ShaderFile/CubeShader.glslf");

  Cubes *cubes = new Cubes();

  glm::mat4 model = glm::mat4(1.0f);

  Camera *camera = new Camera(glm::vec3(-6, 5, -10), glm::radians(70.0f));

  camera->Rotation = glm::mat4(1.0f);
  camera->Rotate(-0.65, 10, 0);

  float lastTime = glfwGetTime();
  float deltaTime = 0.0f;

  float currentTime;

  float camX = 10.0f;
  float camY = -0.65f;

  float speed = 7;

  glClearColor(0.6f, 0.62f, 0.65f, 1.);

  bool flag = false;

  glEnable(GL_DEPTH_TEST);

  while (!Window::isShouldClose()) {

    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (Events::justPressed(GLFW_KEY_TAB)) {
      Events::toogleCursor();
    }

    if (Events::justPressed(GLFW_KEY_SPACE)) {
      flag ? glClearColor(0.1, 0.4, 0.6, 0.1) : glClearColor(0., 0.7, 0.3, 1.);
      flag = !flag;
    }

    if (Events::justPressed(GLFW_KEY_1)) {
      cubes->MoveUpX(true);
    }

    if (Events::justPressed(GLFW_KEY_2)) {
      cubes->MoveUpX(false);
    }

    if (Events::justPressed(GLFW_KEY_3)) {
      cubes->MoveUpY(true);
    }

    if (Events::justPressed(GLFW_KEY_4)) {
      cubes->MoveUpY(false);
    }

    if (Events::justPressed(GLFW_KEY_5)) {
      cubes->MoveUpZ(true);
    }

    if (Events::justPressed(GLFW_KEY_6)) {
      cubes->MoveUpZ(false);
    }

    if (Events::justPressed(GLFW_KEY_T)) {
      cubes->MoveDownX(true);
    }

    if (Events::justPressed(GLFW_KEY_Y)) {
      cubes->MoveDownX(false);
    }

    if (Events::justPressed(GLFW_KEY_U)) {
      cubes->MoveDownY(true);
    }

    if (Events::justPressed(GLFW_KEY_I)) {
      cubes->MoveDownY(false);
    }

    if (Events::justPressed(GLFW_KEY_O)) {
      cubes->MoveDownZ(true);
    }

    if (Events::justPressed(GLFW_KEY_P)) {
      cubes->MoveDownZ(false);
    }

    if (Events::justPressed(GLFW_KEY_M)) {
      cubes->RandowMove();
    }

    if (Events::justPressed(GLFW_KEY_B)) {
      cubes->AutomaticMove();
    }

    if (Events::justPressed(GLFW_KEY_F1)) {
      cubes->SaveCube("../Saves/CubicRubic.cub") ? log("Save Cube!")
                                                 : log("Error save cube");
    }

    if (Events::justPressed(GLFW_KEY_F2)) {
      cubes->LoadCube("../Saves/CubicRubic.cub") ? log("Load Cube!")
                                                 : log("Error load cube");
    }

    if (Events::justPressed(GLFW_KEY_ESCAPE)) {
      Window::setShouldClose(true);
    }

    if (Events::isPressed(GLFW_KEY_S)) {
      camera->position -= camera->Front * deltaTime * speed;
    }

    if (Events::isPressed(GLFW_KEY_W)) {
      camera->position += camera->Front * deltaTime * speed;
    }

    if (Events::isPressed(GLFW_KEY_D)) {
      camera->position += camera->Right * deltaTime * speed;
    }

    if (Events::isPressed(GLFW_KEY_A)) {
      camera->position -= camera->Right * deltaTime * speed;
    }

    if (Events::cursorLocked) {
      camY += -Events::deltaY / Window::SizeY;
      camX += -Events::deltaX / Window::SizeY;

      if (camY < -glm::radians(89.0f)) {
        camY = -glm::radians(89.0f);
      }

      if (camY > glm::radians(89.0f)) {
        camY = glm::radians(89.0f);
      }

      camera->Rotation = glm::mat4(1.0f);
      camera->Rotate(camY, camX, 0);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CubeShaderProgram->Use();
    CubeShaderProgram->uniformMatrix("projectview", camera->getProjection() *
                                                        camera->getView());
   
    for (size_t index = 0; index < 27; ++index){
       CubeShaderProgram->uniformMatrix("model", cubes -> ACubes[index]->model);
    }
   
    cubes->Draw();

    Window::SwapBuffers();
    Events::pullEvents();
  }

  delete CubeShaderProgram;
  delete cubes;

  delete camera;

  glfwTerminate();

  return 0;
}
