#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
class Shader {
private:
    unsigned int id;
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use();
    void setMat4(std::string name, glm::mat4 matrix);
};
#endif //SHADER_H
