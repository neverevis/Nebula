#include "../Nebula.h"
#include "../Nebula/Shader.h"

class Sandbox : public Application {
public:
    Shader shader;
    Mesh mesh;
    Camera camera;
    glm::mat4 model = glm::mat4(1);
    glm::mat4 model1 = glm::mat4(1);
    float rotation = 0;

    Sandbox() :
    Application(800,800,"Nebula Engine Sandbox"), shader("vertex.glsl","frag.glsl")
    {
        mesh.vertices = {
            -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,  1.0f,    0.0f,  0.0f, //       4-----------5
             0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f,  1.0f,  0.0f,  1.0f,    0.0f,  0.0f, //      /|          /|
             0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f,  0.0f,  1.0f,  1.0f,    0.0f,  0.0f, //     / |         / |
            -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f,  1.0f,  0.0f,  1.0f,    0.0f,  0.0f, //    0--|--------1  |
                                                                                                      //    |  7        |  6
            -0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,  1.0f,    0.0f,  0.0f, //    | /         | /
             0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f,  1.0f,  0.0f,  1.0f,    0.0f,  0.0f, //    |/          |/
             0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f,  0.0f,  1.0f,  1.0f,    0.0f,  0.0f, //    3-----------2
            -0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f,  1.0f,  0.0f,  1.0f,    0.0f,  0.0
        };

        mesh.triangles = {
            0,1,2,2,3,0,
            4,5,6,6,7,4,

            0,4,7,7,3,0,
            1,5,6,6,2,1,

            0,1,5,5,4,0,
            3,2,6,6,7,3
        };

        renderer.setCamera(camera);
        renderer.setClearColor(0.0,0.0,0.0,0.5);
    }


    void step(float dt) override {
        rotation += 50 * dt;
        model = glm::rotate(glm::mat4(1),glm::radians(rotation),glm::vec3(0.0,1.0,0.0));
        model = glm::scale(model,glm::vec3(0.5,0.5,0.5));
        
        model1 = glm::scale(model,glm::vec3(0.5,0.5,0.5));
        model1 = glm::translate(model,glm::vec3(-1.0,0.0,0.0));


        renderer.begin();
        renderer.draw(mesh,shader, model);
        renderer.draw(mesh,shader, model1);
        renderer.end();
    }
};

int main() {
    Sandbox* sandbox = new Sandbox;
    sandbox->run();
    delete sandbox;
}
