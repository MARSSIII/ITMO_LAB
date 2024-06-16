#include "Cube.hpp"

#include <GLFW/glfw3.h>
#include <iostream>

#define log(x) std::cerr << x << std::endl

#define X(index) index
#define Y(index) index + 1
#define Z(index) index + 2

#define Icolor1(index) index + 3
#define Icolor2(index) index + 4
#define Icolor3(index) index + 5

Cube::Cube() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  CountColor = 0;

  SiteA = color::BLACK;
  SiteB = color::BLACK;
  SiteC = color::BLACK;
  SiteD = color::BLACK;
  SiteE = color::BLACK;
  SiteF = color::BLACK;

  float defaultX1 = 1.0f, defaultX2 = -1.0f;
  float defaultY1 = 1.0f, defaultY2 = -1.0f;
  float defaultZ1 = 1.0f, defaultZ2 = -1.0f;

  GLfloat defaultvertices[] = {

      //   F
      // A B C D
      //   E

      // Координаты        // Цвета

      // A
      -1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,

      // C

      -1.f,
      -1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      -1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      -1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,

      // E

      -1.f,
      1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      -1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,

      // F

      1.f,
      1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      -1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,

      // B

      -1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      -1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      -1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      -1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      -1.f,
      -1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,

      // D

      -1.f,
      1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      1.f,
      -1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      1.f,
      1.f,
      1.0f,
      1.0f,
      1.0f,
      1.f,
      1.f,
      1.f,
      0.0f,
      0.0f,
      0.0f,
      -1.f,
      1.f,
      1.f,
      0.0f,
      0.0f,
      0.0f,
      -1.f,
      1.f,
      -1.f,
      0.0f,
      0.0f,
      0.0f,
  };

  for (int i = 0; i < 216; ++i) {
    vertices[i] = defaultvertices[i];
  }

  for (int index = 0, count = 0; count < 36; index += 6, ++count) {

    vertices[Icolor1(index)] = 0.0f;
    vertices[Icolor2(index)] = 0.0f;
    vertices[Icolor3(index)] = 0.0f;
  }

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

Cube::~Cube() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}

void Cube::RotateCube(glm::vec3 Rvec){
  model = glm::rotate(model, (float)glfwGetTime(), Rvec);
}

void Cube::SetColor(color NewColor, site Site) {

  int Start;
  int End;

  float color1;
  float color2;
  float color3;

  switch (Site) {
  case 0:
    SiteA = NewColor;
    break;
  case 1:
    SiteC = NewColor;
    break;
  case 2:
    SiteE = NewColor;
    break;
  case 3:
    SiteF = NewColor;
    break;
  case 4:
    SiteB = NewColor;
    break;
  case 5:
    SiteD = NewColor;
    break;
  }

  switch (NewColor) {
  case 0: // RED
    color1 = 1.0f;
    color2 = 0.0f;
    color3 = 0.0f;
    break;

  case 1: // GREEN
    color1 = 0.0f;
    color2 = 1.0f;
    color3 = 0.0f;
    break;

  case 2: // BLUE
    color1 = 0.0f;
    color2 = 0.0f;
    color3 = 1.0f;
    break;

  case 3: // WHITE
    color1 = 1.0f;
    color2 = 1.0f;
    color3 = 1.0f;
    break;

  case 4: // YELLOW
    color1 = 1.0f;
    color2 = 1.0f;
    color3 = 0.0f;
    break;

  case 5: // ORANGE
    color1 = 1.0f;
    color2 = 0.67f;
    color3 = 0.0f;
    break;

  default:
    color1 = 0.0f;
    color2 = 0.0f;
    color3 = 0.0f;
    break;
  }

  switch (Site) {
  case 0: // A
    Start = 0;
    End = 5;
    break;

  case 1: // B
    Start = 6;
    End = 11;
    break;

  case 2: // C
    Start = 12;
    End = 17;
    break;

  case 3: // D
    Start = 18;
    End = 23;
    break;

  case 4: // E
    Start = 24;
    End = 29;
    break;

  case 5: // F
    Start = 30;
    End = 35;
    break;

  default:
    log("Wrong Site");
    break;
  }

  for (int index = 0, count = 0; count <= End; index += 6, ++count) {
    if (count >= Start) {
      vertices[Icolor1(index)] = color1;
      vertices[Icolor2(index)] = color2;
      vertices[Icolor3(index)] = color3;
    }
  }

  m_UpdateCube();
}

void Cube::RotateColorX(bool Diraction) {

  // Diraction - true = left
  // Diraction - false = right

  color tmpA = SiteA;
  color tmpC = SiteC;
  color tmpE = SiteE;
  color tmpF = SiteF;

  if (Diraction) {

    SetColor(tmpA, site::F);
    SetColor(tmpF, site::C);
    SetColor(tmpC, site::E);
    SetColor(tmpE, site::A);

  } else {

    SetColor(tmpA, site::E);
    SetColor(tmpE, site::C);
    SetColor(tmpC, site::F);
    SetColor(tmpF, site::A);
  }
}

void Cube::RotateColorY(bool Diraction) {

  // Diraction - true = forward
  // Diraction - false = back

  color tmpF = SiteF;
  color tmpB = SiteB;
  color tmpE = SiteE;
  color tmpD = SiteD;

  if (Diraction) {

    SetColor(tmpB, site::F);
    SetColor(tmpF, site::D);
    SetColor(tmpD, site::E);
    SetColor(tmpE, site::B);

  } else {

    SetColor(tmpB, site::E);
    SetColor(tmpE, site::D);
    SetColor(tmpD, site::F);
    SetColor(tmpF, site::B);
  }

  m_UpdateCube();
}

void Cube::RotateColorZ(bool Diraction) {

  // Diraction - true = right
  // Diraction - false = left

  color tmpA = SiteA;
  color tmpB = SiteB;
  color tmpC = SiteC;
  color tmpD = SiteD;

  if (Diraction) {

    SetColor(tmpA, site::D);
    SetColor(tmpD, site::C);
    SetColor(tmpC, site::B);
    SetColor(tmpB, site::A);

  } else {

    SetColor(tmpB, site::C);
    SetColor(tmpC, site::D);
    SetColor(tmpD, site::A);
    SetColor(tmpA, site::B);
  }

  m_UpdateCube();
}

void Cube::ShiftXYZ(float shiftX, float shiftY, float shiftZ) {
  for (int index = 0, count = 0; count < 36; index += 6, ++count) {
    vertices[X(index)] += shiftX;
    vertices[Y(index)] += shiftY;
    vertices[Z(index)] += shiftZ;
  }

  m_UpdateCube();
}

void Cube::ShiftX(float shift) {
  for (int index = 0, count = 0; count < 36; index += 6, ++count) {
    vertices[X(index)] += shift;
  }

  m_UpdateCube();
}

void Cube::ShiftY(float shift) {
  for (int index = 0, count = 0; count < 36; index += 6, ++count) {
    vertices[Y(index)] += shift;
  }

  m_UpdateCube();
}

void Cube::ShiftZ(float shift) {
  for (int index = 0, count = 0; count < 35; index += 6, ++count) {
    vertices[Z(index)] += shift;
  }

  m_UpdateCube();
}

void Cube::draw() {
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}

void Cube::m_UpdateCube() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (GLvoid *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                        (GLvoid *)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
}
