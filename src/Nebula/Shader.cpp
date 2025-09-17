#include "Shader.h"

#include "glad/glad.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::ifstream vertexFile(vertexPath);
    std::ifstream fragmentFile(fragmentPath);

    bool loaded = true;

    if (!vertexFile.is_open()) {
        std::cerr << "[Shader] Error loading vertex shader file." << std::endl;
        loaded = false;
    }
    if (!fragmentFile.is_open()) {
        std::cerr << "[Shader] Error loading fragment shader file." << std::endl;
        loaded = false;
    }

    if (loaded) {
        std::stringstream vertexStream;
        std::stringstream fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        std::string vertexCode = vertexStream.str();
        std::string fragmentCode = fragmentStream.str();

        const char* vertexSource = vertexCode.c_str();
        const char* fragmentSource = fragmentCode.c_str();

        vertexFile.close();
        fragmentFile.close();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShader =glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vertexShader,1,&vertexSource,nullptr);
        glShaderSource(fragmentShader,1,&fragmentSource, nullptr);

        glCompileShader(vertexShader);
        glCompileShader(fragmentShader);

        int success;
        char infoLog[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
            std::cerr << "[Shader] Vertex shader compilation failed:\n" << infoLog << std::endl;
        }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
            std::cerr << "[Shader] Fragment shader compilation failed:\n" << infoLog << std::endl;
        }

        id = glCreateProgram();

        glAttachShader(id,vertexShader);
        glAttachShader(id,fragmentShader);
        glLinkProgram(id);

        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(id, 512, nullptr, infoLog);
            std::cerr << "[Shader] Program linking failed:\n" << infoLog << std::endl;
        }else {
            std::cout << "[Shader] Shader successfully linked!" << std::endl;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() {
    glUseProgram(id);
}

