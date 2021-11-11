// fragment shader

// glsl version declaration
#version 430 core

layout (location = 3) uniform sampler2D albedo;
layout (location = 4) uniform vec3 ambientLight;
layout (location = 5) uniform vec3 lightDirection;

// inputs from the vertex shader
in vec4 vertColor;
in vec2 vertUVs;
in vec3 vertNormal;

// the fragment shader has one output (by default) - the color of the fragment
out vec4 outColor;

float clamp(float value, float minV, float maxV)
{
  return min(max(minV, value), maxV);
}

void main()
{
  float d = min(1,max(0.0f, dot(vertNormal, -lightDirection)));
  vec3 diffuse = vec3(d);

  vec4 texColor = texture(albedo, vertUVs);
  vec4 baseColor = texture(albedo, vertUVs) * vertColor;

  outColor.rgb = baseColor.rgb * (ambientLight + diffuse);
  // outColor.r = min(texColor.r, outColor.r);
  // outColor.g = min(texColor.g, outColor.g);
  // outColor.b = min(texColor.b, outColor.b);
  outColor.a = baseColor.a;
};