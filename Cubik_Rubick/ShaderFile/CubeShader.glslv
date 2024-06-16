#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 a_color;

out vec3 ourColor;

uniform mat4 model;
uniform mat4 projectview;

void main(){
  ourColor = a_color;
  gl_Position = projectview * model * vec4(position, 1.0f);
}
