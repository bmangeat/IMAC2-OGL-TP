#version 330 core

layout(location=0) in vec2 aVertexPosition;

out vec2 vPosition;

void main() {
	vPosition = aVertexPosition;
	gl_Position = vec4(aVertexPosition, 0, 1);
}
