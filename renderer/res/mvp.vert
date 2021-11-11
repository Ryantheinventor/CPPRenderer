//vertex shader

//glsl version declaration
#version 430 core

//vertex attributes
layout (location = 0) in vec4 position; // index 0 - the vertex position
layout (location = 1) in vec4 colors; // index 1 - the vertex color
layout (location = 2) in vec2 uvs; // index 2 - the vertex UV
layout (location = 3) in vec3 normal; // index 3 - the vertiex normal

//uniforms
layout (location = 0) uniform mat4 proj;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 model;

out vec4 vertColor;
out vec2 vertUVs;
out vec3 vertNormal;

//each shader needs a main function
void main()
{
  vertUVs = uvs;
  vertColor = colors;
  gl_Position = proj * view * model * position;

  vertNormal = mat3(transpose(inverse(model))) * normal;

};