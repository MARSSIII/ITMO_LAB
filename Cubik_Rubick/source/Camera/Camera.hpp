#pragma once

#include <glm/ext.hpp>
#include <glm/glm.hpp>

class Camera {
public:
  Camera(glm::vec3 position, float fov)
      : position(position), fov(fov), Rotation(1.0f) {
    UpdatesVector();
  }

  float fov;
  glm::vec3 position;

  glm::vec3 Up;
  glm::vec3 Right;
  glm::vec3 Front;

  glm::mat4 Rotation;

  void Rotate(float X, float Y, float Z);

  glm::mat4 getProjection();
  glm::mat4 getView();

private:
  void UpdatesVector();
};
