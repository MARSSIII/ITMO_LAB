#include "WindowEvents.hpp"

#include <GLFW/glfw3.h>

#include <cstring>

#define _MOUSE_BUTTONS 1024

bool *Events::_keys;
unsigned int *Events::_frames;
unsigned int Events::_currentFrame = 0;

float Events::deltaX = 0.0f;
float Events::deltaY = 0.0f;

float Events::X = 0.0f;
float Events::Y = 0.0f;

bool Events::cursorLocked = false;
bool Events::cursorStarted = false;

void CursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
  if (Events::cursorStarted) {
    Events::deltaX += xPos - Events::X;
    Events::deltaY += yPos - Events::Y;
  } else {
    Events::cursorStarted = true;
  }

  Events::X = xPos;
  Events::Y = yPos;
}

// Callback на нажатие мыши
void MouseButtonCallback(GLFWwindow *window, int button, int action, int mode) {
  if (action == GLFW_PRESS) {
    Events::_keys[_MOUSE_BUTTONS + button] = true;
    Events::_frames[_MOUSE_BUTTONS + button] = Events::_currentFrame;
  } else if (action == GLFW_RELEASE) {
    Events::_keys[_MOUSE_BUTTONS + button] = false;
    Events::_frames[_MOUSE_BUTTONS + button] = Events::_currentFrame;
  }
}

// Callback на нажатие клавиатуры
void KeyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mode) {
  if (action == GLFW_PRESS) {
    Events::_keys[key] = true;
    Events::_frames[key] = Events::_currentFrame;
  } else if (action == GLFW_RELEASE) {
    Events::_keys[key] = false;
    Events::_frames[key] = Events::_currentFrame;
  }
}

void WindowSizeCallback(GLFWwindow *window, int SizeX, int SizeY) {
  glViewport(0, 0, SizeX, SizeY);
  Window::SizeX = SizeX;
  Window::SizeY = SizeY;
}

int Events::initialize() {
  GLFWwindow *window = Window::window;

  // 1024 - для клавиатуры, остальные для мыши
  _keys = new bool[1032];
  _frames = new unsigned int[1032];

  memset(_keys, false, 1032 * sizeof(bool));
  memset(_frames, 0, 1032 * sizeof(unsigned int));

  glfwSetKeyCallback(window, KeyCallback);
  glfwSetMouseButtonCallback(window, MouseButtonCallback);
  glfwSetCursorPosCallback(window, CursorPositionCallback);
  glfwSetWindowSizeCallback(window, WindowSizeCallback);
  return 0;
}

bool Events::clicked(int button) {
  int index = _MOUSE_BUTTONS + button;
  return _keys[index];
}

bool Events::justClicked(int button) {
  int index = _MOUSE_BUTTONS + button;
  return (_keys[index] && _frames[index] == _currentFrame);
}

void Events::toogleCursor() {
  cursorLocked = !cursorLocked;
  Window::setCursorMode(cursorLocked ? GLFW_CURSOR_DISABLED
                                     : GLFW_CURSOR_NORMAL);
}

bool Events::isPressed(int keyCode) {
  if (keyCode < 0 || keyCode >= _MOUSE_BUTTONS) {
    return false;
  }

  return _keys[keyCode];
}

bool Events::justPressed(int keyCode) {
  if (keyCode < 0 || keyCode >= _MOUSE_BUTTONS) {
    return false;
  }

  return (_keys[keyCode] && _frames[keyCode] == _currentFrame);
}

void Events::pullEvents() {
  deltaX = 0.0f;
  deltaY = 0.0f;

  ++_currentFrame;
  glfwPollEvents();
}
