#ifndef EBO_H
#define EBO_H
#include <vector>
#include <glad/glad.h>
class EBO {
public:
    GLuint ID;
    EBO();
    ~EBO();

    void operator=(const std::vector<unsigned int>& triangles);
    int getCount();
private:
    int count;
};
#endif
