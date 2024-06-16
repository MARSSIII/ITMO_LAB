#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>

void Shader::Use() { glUseProgram(ID); }

void Shader::uniformMatrix(std::string name, glm::mat4 matrix) {
  GLuint TransformLoc = glGetUniformLocation(ID, name.c_str());
  glUniformMatrix4fv(TransformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

extern Shader *LoadShader(std::string VertexFile, std::string FragmentFile) {
  std::string VertexCode;
  std::string FragmentCode;

  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::badbit);
  try {
    vShaderFile.open(VertexFile);
    fShaderFile.open(FragmentFile);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    VertexCode = vShaderStream.str();
    FragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure &exp) {
    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    return nullptr;
  }

  const GLchar *vShaderCode = VertexCode.c_str();
  const GLchar *fShaderCode = FragmentCode.c_str();

  GLuint Vertex, Fragment;
  GLint Success;
  GLchar InfoLog[512];

  // Vertex
  // создание шейдера
  Vertex = glCreateShader(GL_VERTEX_SHADER);

  // загрузка исходного кода шейдеров
  glShaderSource(Vertex, 1, &vShaderCode, nullptr);
  // compilation
  glCompileShader(Vertex);
  // информация о шейдере
  glGetShaderiv(Vertex, GL_COMPILE_STATUS, &Success);

  // проверка, что шейдер прошел компиляцию
  if (!Success) {
    glGetShaderInfoLog(Vertex, 512, nullptr, InfoLog);
    std::cerr << "SHADER compl. failed" << std::endl;
    std::cerr << InfoLog << std::endl;
    return nullptr;
  }

  // Fragment
  // создание шейдера
  Fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(Fragment, 1, &fShaderCode, nullptr);
  glCompileShader(Fragment);
  glGetShaderiv(Fragment, GL_COMPILE_STATUS, &Success);

  // проверка, что шейдер прошел компиляцию
  if (!Success) {
    glGetShaderInfoLog(Fragment, 512, nullptr, InfoLog);
    std::cerr << "SHADER compl. failed" << std::endl;
    std::cerr << InfoLog << std::endl;
    return nullptr;
  }

  // Создание Шейдерной программы
  GLuint ID = glCreateProgram();

  glAttachShader(ID, Vertex);
  glAttachShader(ID, Fragment);

  glLinkProgram(ID);
  glGetProgramiv(ID, GL_LINK_STATUS, &Success);

  glDeleteShader(Vertex);
  glDeleteShader(Fragment);

  if (!Success) {
    glGetProgramInfoLog(ID, 512, nullptr, InfoLog);
    std::cerr << "Shader programm link failed" << std::endl;
    std::cerr << InfoLog << std::endl;

    glDeleteProgram(ID);

    return nullptr;
  }

  return new Shader(ID);
}
