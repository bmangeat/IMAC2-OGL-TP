#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>
#include <vector>

using namespace glimac;

struct Vertex2DColor{
  glm::vec2 m_position;
  glm::vec3 m_color;

  Vertex2DColor(){};
  Vertex2DColor(glm::vec2 position, glm::vec3 color){
    m_position = position;
    m_color = color;
  };
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 800, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl",
                                  applicationPath.dirPath() + "shaders/triangle.fs.glsl");
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
//
     GLuint vbo, vao;

     float r, n; // r pour rayon et n pour nombre de triangle dans le cercle

     r = 0.5;
     n = 720;

     glGenBuffers(1, &vbo);

     glBindBuffer(GL_ARRAY_BUFFER, vbo);
       std::vector<Vertex2DColor> vertices;

       vertices.emplace_back(
         glm::vec2(0,0),
         glm::vec3(0,0,0));

       for (float i = 0; i < 2*glm::pi<float>(); i=i+(2*glm::pi<float>())/n) {
         vertices.emplace_back(
           glm::vec2(
             r*glm::cos(i),
             r*glm::sin(i)
           ),
           glm::vec3(1,0.8f,0)
         );


       }

       glBufferData(GL_ARRAY_BUFFER, 1+n*sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);
     glBindBuffer(GL_ARRAY_BUFFER, 0);

     // Création IBO
     GLuint ibo;
     glGenBuffers(1, &ibo);

     //  On bind sur GL_ELEMENT_ARRAY_BUFFER, cible reservée pour les IBOs
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

     // Tableau d'indices: ce sont les indices des sommets à dessiner
    // On en a 6 afin de former deux triangles
    // Chaque indice correspond au sommet correspondant dans le VBO

      std::vector<uint32_t> indices;

      for (size_t i = 0; i <= n+1; i++) {
        indices.emplace_back(i);
      };

    // On remplit l'IBO avec les indices
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, (n+1) * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    // Comme d'habitude on debind avant de passer à autre chose
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
     
     glGenVertexArrays(1, &vao);

     glBindVertexArray(vao);
      const GLuint VERTEX_ATTR_POSITION = 3;
      const GLuint VERTEX_ATTR_COLOR = 8;

      glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

        glVertexAttribPointer(
          VERTEX_ATTR_POSITION ,
          2,
          GL_FLOAT,
          GL_FALSE,
          sizeof(Vertex2DColor),
          (const GLvoid*)(offsetof(Vertex2DColor, m_position))
        );
        glVertexAttribPointer(
          VERTEX_ATTR_COLOR ,
          3,
          GL_FLOAT,
          GL_FALSE,
          sizeof(Vertex2DColor),
          (const GLvoid*)(offsetof(Vertex2DColor, m_color))
        );
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

         glClear(GL_COLOR_BUFFER_BIT);

         glBindVertexArray(vao);
           glDrawArrays(GL_TRIANGLES, 0, 3*n);
         glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vao);
    glDeleteVertexArrays(1, &vbo);

    return EXIT_SUCCESS;
}
