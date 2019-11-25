#version 330 core

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vFragColor;
out vec2 vPosition;

mat3 translate(float tx, float ty){
  mat3 M = mat3(vec3(1,0,0), vec3(0,1,0), vec3(tx, ty, 1));
  return M;
}

mat3 scale(float sx, float sy){
  mat3 M = mat3(vec3(sx,0,0), vec3(0,sy,0), vec3(0, 0, 1));
  return M;
}

mat3 rotate(float a){
  mat3 M = mat3(vec3(cos(radians(a)),sin(radians(a)),0), vec3(-sin(radians(a)), cos(radians(a)),0), vec3(0, 0, 1));
  return M;
}

void main(){

// Translation du triangle de (0.5,0.5)
  // vec2 vecTranslation = vec2(0.5,0.5);
  // vFragColor = aVertexColor;
  // gl_Position = vec4(aVertexPosition + vecTranslation, 0, 1);


// Scaling global de la taille du triangle
  // int alpha = 2;
  // vFragColor = aVertexColor;
  // gl_Position = vec4(aVertexPosition*alpha , 0, 1);

// Scaling sur axeX et axeY
  //vec2 vecScaling = vec2(2, 0.5);
  //vFragColor = aVertexColor;
  //gl_Position = vec4(aVertexPosition*vecScaling, 0, 1);

// Utilisation d'une matrice permettant la translation, rotation, scale
  // mat3 M = translate(0.5, 0.5);
  // mat3 M = scale(2.0,0.5);
  // mat3 M = rotate(45);

// Multiplier les transformations du triangle

  // mat3 M = mat3(1.f);
  // M *= translate(0.5,0);
  // M *= rotate(45);
  // M *= scale(0.5, 0.5);
  // vec2 transformedVP = (M*vec3(aVertexPosition, 1)).xy;

  // vFragColor = aVertexColor;
  // gl_Position = vec4(transformedVP, 0, 1);

// Transformer le triangle en particule = traitement de la couleur dans le FS

  vFragColor = aVertexColor;
  vPosition = aVertexPosition;

  gl_Position = vec4(aVertexPosition, 0, 1);

// Texture procédurale

  //vFragColor = aVertexColor*length(fract(5.0*aVertexPosition));
  //gl_Position = vec4(aVertexPosition, 0, 1);


}
