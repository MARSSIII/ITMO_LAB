#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

enum color { RED, GREEN, BLUE, WHITE, YELLOW, ORANGE, BLACK };

enum site { A, C, E, F, B, D };

class Cube {
public:
  Cube();
  ~Cube();

  void SetColor(color NewColor, site Site);

  void ShiftXYZ(float shiftX, float shiftY, float shiftZ);

  void ShiftX(float shift);
  void ShiftY(float shift);
  void ShiftZ(float shift);

  void RotateCube(glm::vec3 Rvec);

  void RotateColorX(bool Diraction);
  void RotateColorY(bool Diraction);
  void RotateColorZ(bool Diraction);

  void draw();

  int CountColor;

  GLuint VAO;
  GLuint VBO;

  glm::mat4 model = glm::mat4(1.0f);

  GLfloat vertices[216];

  color SiteA;
  color SiteB;
  color SiteC;
  color SiteD;
  color SiteE;
  color SiteF;

  void m_UpdateCube();
};
