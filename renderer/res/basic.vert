//vertex shader

//glsl version declaration
#version 430 core

//vertex attributes
layout (location = 0) in vec4 position; // index 0 - the vertex position
layout (location = 1) in vec4 colors; // index 1 - the vertex color

out vec4 vertColor;

//each shader needs a main function
void main()
{
  
  vertColor = colors;


  // the vertex shader MUST write to gl_Position before returning
  //
  // this is the position of the vertex in clip-space
  gl_Position = position;
};