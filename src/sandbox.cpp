#include <platform/window.h>
#include <platform/gl_renderer.h>
#include <opengl/shader.h>

int main()
{
    // --------------------
    // Janela + OpenGL
    // --------------------
    NBL::Window w(800, 800, "Sandbox", BUTTON_MENU | MINIMIZE_BUTTON);
    gl_load_context(w);
    gl_load_functions();
    w.show();

    // --------------------
    // Shaders
    // --------------------
    Shader shader("src/shaders/default.vert", "src/shaders/default.frag");

    // --------------------
    // Dados do triângulo
    // --------------------
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // --------------------
    // VAO + VBO (DSA)
    // --------------------
    GLuint VAO, VBO;

    glCreateVertexArrays(1, &VAO);
    glCreateBuffers(1, &VBO);

    glNamedBufferData(
        VBO,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // binding index 0
    glVertexArrayVertexBuffer(
        VAO,
        0,
        VBO,
        0,
        3 * sizeof(float)
    );

    // layout(location = 0)
    glEnableVertexArrayAttrib(VAO, 0);

    glVertexArrayAttribFormat(
        VAO,
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0
    );

    glVertexArrayAttribBinding(
        VAO,
        0,
        0
    );

    // --------------------
    // Loop principal
    // --------------------
    while (!w.should_close())
    {
        w.poll_events();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        w.swap_buffers();
    }
}
