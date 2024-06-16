#include "Camera.hpp"

#include "../Window/window.hpp"

void Camera::UpdatesVector() {
  Front = glm::vec3(Rotation * glm::vec4(0, 0, -1, 1));
  Right = glm::vec3(Rotation * glm::vec4(1, 0, 0, 1));
  Up = glm::vec3(Rotation * glm::vec4(0, 1, 0, 1));
}

void Camera::Rotate(float X, float Y, float Z) {
  Rotation = glm::rotate(Rotation, Z, glm::vec3(0, 0, 1));
  Rotation = glm::rotate(Rotation, Y, glm::vec3(0, 1, 0));
  Rotation = glm::rotate(Rotation, X, glm::vec3(1, 0, 0));

  UpdatesVector();
}

glm::mat4 Camera::getProjection() {
  float aspect = (float)Window::SizeX / (float)Window::SizeY;

  // Угол зрения по Y, соотношение сторон окна, ближайшая плоскость фрустума,
  // дальняя плоскость фрустума
  return glm::perspective(fov, aspect, 0.1f, 100.0f);
}

// то откуда и куда и где будет смотреть камера
glm::mat4 Camera::getView() {
  // позиция камеры , точка куда смотрит камера, верх камеры
  return glm::lookAt(position, position + Front, Up);
}
