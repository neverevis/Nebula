#pragma once

#include <platform/gl_renderer.h>
#include <string>

class Shader
{
public:
    GLuint id;

    Shader(const std::string& vertex, const std::string& fragment);
    ~Shader();

    void use();
};