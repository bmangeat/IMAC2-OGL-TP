#version 330 core

in vec3 vFragColor;

out vec3 fFragColor;

void main(){
  fFragColor.x = vFragColor.x + vFragColor.xy + vFragColor.z/3;
  fFragColor.y = vFragColor.x + vFragColor.xy + vFragColor.z/3;
  fFragColor.z = vFragColor.x + vFragColor.xy + vFragColor.z/3;

}
