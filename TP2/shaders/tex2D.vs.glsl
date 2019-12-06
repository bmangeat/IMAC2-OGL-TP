#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 0) in vec2 aVertexTexture;


out vec2 vFragTexture;
out vec2 vPosition;

void main(){
    vFragTexture = aVertexTexture;
    vPosition = aVertexPosition;

    gl_Position = vec4(aVertexPosition, 0, 1);
}