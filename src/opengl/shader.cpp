#include <opengl/shader.h>
#include <utils/file_reader.h>
#include <utils/log.h>
#include <vector>
#include <iostream>

Shader::Shader(const std::string& vertex, const std::string& fragment)
{
    int vertex_id = glCreateShader(GL_VERTEX_SHADER);
    int fragment_id = glCreateShader(GL_FRAGMENT_SHADER);

    std::string v = read_file(vertex);
    std::string f = read_file(fragment);

    const char* vertex_src = v.c_str();
    const char* frag_src = f.c_str();

    glShaderSource(vertex_id, 1, &vertex_src , nullptr);
    glShaderSource(fragment_id, 1, &frag_src , nullptr);

    glCompileShader(vertex_id);
    glCompileShader(fragment_id);

    GLint success;
    GLint log_size = 0;

    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);
    glGetShaderiv(vertex_id, GL_INFO_LOG_LENGTH, &log_size);

    if(!success)
    {
        std::vector<char> log(log_size);
        glGetShaderInfoLog(vertex_id, log_size, nullptr, log.data());
        std::cout << log.data() << std::endl;
    }

    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragment_id, GL_INFO_LOG_LENGTH, &log_size);

    if(!success)
    {
        std::vector<char> log(log_size);
        glGetShaderInfoLog(fragment_id, log_size, nullptr, log.data());
        printf("%s",log.data());
    }

    id = glCreateProgram();
    glAttachShader(id, vertex_id);
    glAttachShader(id, fragment_id);
    glLinkProgram(id);
}

Shader::~Shader()
{
    
}

void Shader::use()
{
    glUseProgram(id);
}