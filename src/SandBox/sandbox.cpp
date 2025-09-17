#include "../Nebula.h"
#include "../Nebula/Shader.h"

class Sandbox : public Application{
public:
    Shader shader;
    unsigned int VAO, VBO;
    Sandbox() :
    shader("vertex.glsl","frag.glsl")
    {
        float vertices[] = {
            0.0, 0.5, 0.0,
           -0.5,-0.5, 0.0,
            0.5,-0.5, 0.0
       };
        glCreateVertexArrays(1,&VAO);
        glCreateBuffers(1,&VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
        renderer.setClearColor(0.0,0.0,0.0,1.0);
    }
    void step() override {
        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
    }
};

int main() {
    Sandbox* sandbox = new Sandbox;
    sandbox->run();
    delete sandbox;
}
