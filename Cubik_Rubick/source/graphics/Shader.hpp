#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

// шейдерная программа
//
// в openGl шейдеры это часть шейдерной программы, то в данном движке шейдером будет называться именно шейдерная
// программа Как и у любого OpenGL объекта у шейдеров есть id, который мы и будем передавать в конструкторе

typedef unsigned int uint;

class Shader {
  public:
	Shader(uint ID) : ID(ID){};

	~Shader() { glDeleteProgram(ID); }

	Shader(const Shader& other) = default;

	void Use();
	void uniformMatrix(std::string name, glm::mat4 matrix);

  private:
	uint ID;
};

extern Shader* LoadShader(std::string VertexFile, std::string FragmentFile);
