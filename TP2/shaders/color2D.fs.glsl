#version 330 core

in vec3 vFragColor;
in vec2 vPosition;

out vec3 fFragColor;

void main(){

  float a = 1.5f;
  float b = 60.f;
  float distance = distance(vPosition, vec2(0,0));
  float textureColored = a*exp(-b*distance*distance);


  fFragColor = vFragColor*textureColored;
}
