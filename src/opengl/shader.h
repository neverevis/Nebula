#pragma once

#include <platform/gl_renderer.h>

class Shader
{
public:
    GLuint id;

    Shader(const char* vertex, const char* fragment);
    ~Shader();
};