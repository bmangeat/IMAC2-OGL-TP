#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>
#include <vector>

using namespace glimac;

struct Vertex2DPosition{
  glm::vec2 m_position;

  Vertex2DPosition(){};
  Vertex2DPosition(glm::vec2 position){
    m_position = position;
  };
};

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/" + argv[1],
                                  applicationPath.dirPath() +  "shaders/" + argv[2]);
    program.use();


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

     GLuint vbo, vao;
     glGenBuffers(1, &vbo);

     glBindBuffer(GL_ARRAY_BUFFER, vbo);
       std::vector<Vertex2DPosition> vertices;


       vertices.emplace_back(
         glm::vec2(-1,-1)
       );
       vertices.emplace_back(
         glm::vec2(-1,1)
       );
       vertices.emplace_back(
         glm::vec2(1,1)
       );
       vertices.emplace_back(
         glm::vec2(1,-1)
       );

       glBufferData(
         GL_ARRAY_BUFFER,
         vertices.size()*sizeof(Vertex2DPosition),
         vertices.data(),
         GL_STATIC_DRAW
       );
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLuint ibo;
    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

      std::vector<uint32_t> indices;
      indices.emplace_back(0);
      indices.emplace_back(1);
      indices.emplace_back(2);
      indices.emplace_back(0);
      indices.emplace_back(2);
      indices.emplace_back(3);



      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size()*sizeof(uint32_t),
        indices.data(),
        GL_STATIC_DRAW
      );
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glGenVertexArrays(1, &vao);
   glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

      const GLuint VERTEX_ATTR_POSITION = 0;
      const GLuint VERTEX_ATTR_COLOR = 1;
      glEnableVertexAttribArray(VERTEX_ATTR_POSITION);

      glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(
          VERTEX_ATTR_POSITION,
          2,
          GL_FLOAT,
          GL_FALSE,
          sizeof(Vertex2DPosition),
          (const GLvoid*)(offsetof(Vertex2DPosition, m_position))
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
          glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vao);
    glDeleteVertexArrays(1, &ibo);
    glDeleteVertexArrays(1, &vbo);

    return EXIT_SUCCESS;
}
