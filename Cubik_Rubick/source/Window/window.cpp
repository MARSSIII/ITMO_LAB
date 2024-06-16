#include "window.hpp"

#include <iostream>

#define log(x) std::cerr << x << std::endl

GLFWwindow *Window::window;
int Window::SizeX = 0;
int Window::SizeY = 0;

int Window::initialize(int SizeX, int SizeY, const char *name) {

  // Инициализация библиотеки
  glfwInit();

  // Создание окна
  // (ширина, высота, NAME, что то интересно, что то тоже интересное)
  window = glfwCreateWindow(SizeX, SizeY, name, nullptr, nullptr);

  // Проверка на создание
  if (!window) {
    glfwTerminate();
    log("Error creat window");
    return -1;
  }

  // Установка созданного окна текущем контекстом
  glfwMakeContextCurrent(window);

  // Сохранение параметров окна
  Window::SizeX = SizeX;
  Window::SizeY = SizeY;

  // Инициализация библиотеки glew
  if (glewInit() != GLEW_OK) {
    log("Can't load glew!");
    return -1;
  }

  // Установка области вывода OpenGL
  glViewport(0, 0, SizeX, SizeY);

  return 1;
}

// Проверка открыто ли окно
bool Window::isShouldClose() { return glfwWindowShouldClose(window); }

// Смена флага окна
void Window::setShouldClose(bool flag) {
  glfwSetWindowShouldClose(window, flag);
}

// Установка режима курсора (в данном случае делает видимым или не видимым)
void Window::setCursorMode(int mode) {
  glfwSetInputMode(window, GLFW_CURSOR, mode);
}

// Меняет буферы окна
void Window::SwapBuffers() { glfwSwapBuffers(window); }

// Завершает работу GLFW и освобаждает все выделенные ресурсы
void Window::terminate() { glfwTerminate(); }
