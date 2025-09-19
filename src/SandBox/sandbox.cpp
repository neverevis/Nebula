#include "../Nebula.h"
#include "../Nebula/Graphics/Shader.h"
#include "../Nebula/Math/Camera.h"

class Sandbox : public Application {
public:
    Shader shader;
    Mesh mesh;
    Camera camera;
    Transform transform;
    Transform floor[20][20];
    float speed = 10;

    Sandbox() :
    Application(800,800,"Nebula Engine Sandbox"), shader("vertex.glsl","frag.glsl")
    {
        mesh.vertices = {
            -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,  1.0f,    0.0f,  0.0f, //       4------------5
             0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f,  1.0f,  0.0f,  1.0f,    0.0f,  0.0f, //      /|           /|
             0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    0.0f,  0.0f,  1.0f,  1.0f,    0.0f,  0.0f, //     / |          / |
            -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  0.0f,    1.0f,  1.0f,  0.0f,  1.0f,    0.0f,  0.0f, //    0--|---------1  |
                                                                                                      //    |  7         |  6
            -0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    1.0f,  0.0f,  0.0f,  1.0f,    0.0f,  0.0f, //    | /          | /
             0.5f,  0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f,  1.0f,  0.0f,  1.0f,    0.0f,  0.0f, //    |/           |/
             0.5f, -0.5f, -0.5f,    0.0f,  0.0f,  0.0f,    0.0f,  0.0f,  1.0f,  1.0f,    0.0f,  0.0f, //    3------------2
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

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                Transform t;
                t.position.x = i;
                t.position.z = j;
                floor[i][j] = t;
            }
        }

        renderer.setCamera(camera);
        renderer.setClearColor(0.0,0.0,0.0,0.5);
    }


    void step(float dt) override {
        update(dt);
        render();
    }

    void update(float dt) {
        glm::vec3 forward = glm::normalize(camera.target - camera.position);
        glm::vec3 right = glm::normalize(glm::cross(forward, camera.up));

        if(window.getKey(GLFW_KEY_W) == GLFW_PRESS)
            camera.position += forward * speed * dt;
        if(window.getKey(GLFW_KEY_S) == GLFW_PRESS)
            camera.position -= forward * speed * dt;
        if(window.getKey(GLFW_KEY_A) == GLFW_PRESS)
            camera.position -= right * speed * dt;
        if(window.getKey(GLFW_KEY_D) == GLFW_PRESS)
            camera.position += right * speed * dt;
        if(window.getKey(GLFW_KEY_SPACE) == GLFW_PRESS)
            camera.position += camera.up * speed * dt;
        if(window.getKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            camera.position += glm::vec3{0.0,-1.0,0.0} * speed * dt;

        camera.target = camera.position + forward;


        transform.rotation.z += 1 * dt;
        transform.rotation.y += 1 * dt;
    }

    void render() {
        renderer.begin();
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++)
            renderer.draw(mesh,shader, floor[i][j]);
        }
        renderer.end();
    }
};

int main() {
    Sandbox* sandbox = new Sandbox;
    sandbox->run();
    delete sandbox;
}
