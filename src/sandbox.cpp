#include <platform/window.h>
#include <platform/gl_renderer.h>
#include <iostream>

float vertices[] = {
    0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f 
};

const char* vertexShaderSrc = R"(
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
out vec3 vertexColor;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor;
}
)";

const char* fragmentShaderSrc = R"(
#version 460 core
out vec4 FragColor;
in vec3 vertexColor;
void main()
{
    FragColor = vec4(vertexColor, 1.0); // vermelho
}
)";

int main()
{
    Window window(800, 800, "sandbox");
    gl_load_context(window);
    gl_load_functions();

    GLuint vao, vbo;
    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);

    //upload data to buffer
    glNamedBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //connect buffer to vao
    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    
    glEnableVertexArrayAttrib(vao, 1);
    glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    glVertexArrayAttribBinding(vao, 1, 0);

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, 6 * sizeof(float));


    //compiling shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Erro Vertex Shader: " << infoLog << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Erro Fragment Shader: " << infoLog << std::endl;
    }

    //link program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "Erro Programa: " << infoLog << std::endl;
    }

    //delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    window.show();
    while(!window.should_close())
    {
        window.poll_events();

        glClearColor(0.5,1,0.5,0.7);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        window.swap_buffers();
    }

    return 0;
}
