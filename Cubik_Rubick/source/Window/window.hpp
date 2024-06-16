#pragma once

#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

class GLFWwindow;

class Window {
public:
  // Размеры окна
  static int SizeX;
  static int SizeY;

  // Инициализация окна
  static int initialize(int SizeX, int SizeY, const char *name);

  // Завершение работы
  static void terminate();

  // Закрытые окна
  static bool isShouldClose();
  static void setShouldClose(bool flag);

  // Смена режима работы курсора
  static void setCursorMode(int mode);

  // Меняет буфферы окна
  static void SwapBuffers();

  static GLFWwindow *window;
};
