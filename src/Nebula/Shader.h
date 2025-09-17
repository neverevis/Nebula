#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <sstream>
#include <fstream>
class Shader {
private:
    unsigned int id;
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use();
};
#endif //SHADER_H
