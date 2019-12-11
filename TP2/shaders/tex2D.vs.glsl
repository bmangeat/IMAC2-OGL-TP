#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;


out vec2 vFragTexture;
out vec2 vPosition;

uniform float uTime;

mat3 rotate(float a){
  mat3 M = mat3(
    vec3(cos(radians(a*uTime)), sin(radians(a*uTime)),0),
    vec3(-sin(radians(a*uTime)), cos(radians(a*uTime)),0),
    vec3(0, 0, 1));
  return M;
}

void main(){
    mat3 M = rotate(10);

    vec2 transformedVP = (M*vec3(aVertexPosition, 1)).xy;

    vFragTexture = aVertexTexture;
    vPosition = aVertexPosition;

    gl_Position = vec4(transformedVP, 0, 1);
}