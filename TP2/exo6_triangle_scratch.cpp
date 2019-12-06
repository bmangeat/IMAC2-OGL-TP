#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

struct Vertex2DUV{
    glm::vec2 m_position;
    glm::vec2 m_texture;

    Vertex2DUV(){};
    Vertex2DUV(glm::vec2 position, glm::vec2 texture){
        m_position = position;
        m_texture = texture;
    }
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

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    GLuint vbo;
    {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        {
            Vertex2DUV vertices[] = {
                    Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0, 0)),
                    Vertex2DUV(glm::vec2(1, -1), glm::vec2(0, 0)),
                    Vertex2DUV(glm::vec2(0, 1), glm::vec2(0, 0))
            };
            glBufferData(GL_ARRAY_BUFFER, 3*sizeof(Vertex2DUV),vertices, GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }

    GLuint vao;

    {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        {
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            {
                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);


                glVertexAttribPointer
                (
                        0,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex2DUV),
                        (const GLvoid*)(offsetof(Vertex2DUV, m_position))
                );

                glVertexAttribPointer
                (
                        1,
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(Vertex2DUV),
                        (const GLvoid*)(offsetof(Vertex2DUV, m_texture))
                );

                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }
            glBindVertexArray(0);
        }
    }



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
        {
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vao);
    glDeleteVertexArrays(1, &vbo);
    return EXIT_SUCCESS;
}
