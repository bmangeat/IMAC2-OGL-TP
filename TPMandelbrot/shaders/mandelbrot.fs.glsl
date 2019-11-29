#version 330

in vec2 vPosition;
out vec3 fFragColor;

vec2 complexSqr(vec2 z){
  return vec2((z.x*z.x)-(z.y*z.y), 2*z.x*z.y);
}

void main(){
  fFragColor.x = 255;
  fFragColor.y = 0;
  fFragColor.z = 0;

  vec2 z = vPosition;
  int i = 0;
  int N = 560;

  while(length(z)<2 && i<N){
    z = complexSqr(z)+ vPosition;
    i++;
  }

  fFragColor = vec3(float(i)/N, 0.9*float(i)/N, 0);
}
