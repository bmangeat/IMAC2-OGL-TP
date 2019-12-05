#version 330 core

in vec3 vFragColor;
in vec2 vPosition;

out vec3 fFragColor;

void main(){

// Texture particule
  // float a = 1.5f;
  // float b = 60.f;
  // float distance = distance(vPosition, vec2(0,0));
  // float textureColored = a*exp(-b*distance*distance);

// Texture procédurale
// #1
// float textureColored = length(fract(5.0*vPosition));

// #2
// float textureColored = length(abs(fract(5.0*vPosition)*2.0-1.0));

// #3
// float textureColored = mod(floor(10.0*vPosition.x)+floor(10.0*vPosition.y), 2.0);

// #4
// float textureColored = smoothstep(0.3, 0.32, length(fract(5.0*vPosition)-0.5));
// #5
//float textureColored = smoothstep(0.4, 0.5, max(abs(fract(8.0*vPosition.x-0.5*mod(floor(8.0*vPosition.y),2.0))-0.5), abs(fract(8.0*vPosition.y)-0.5)));



//fFragColor = vFragColor*textureColored;

fFragColor = vFragColor;
}
