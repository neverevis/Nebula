#include "VAO.h"

VAO::VAO() {
    glCreateVertexArrays(1, &ID);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &ID);
}

void VAO::bind() {
    glBindVertexArray(ID);
}

void VAO::linkVBO(VBO& VBO, GLsizei stride) {
    glVertexArrayVertexBuffer(ID, 0, VBO.ID, 0, stride);

}

void VAO::linkEBO(EBO& EBO) {
    glVertexArrayElementBuffer(ID, EBO.ID);
}

void VAO::linkAttrib(GLuint layout, GLuint components, GLuint offset) {
    //ativa o atributo
    glEnableVertexArrayAttrib(ID, layout);
    //conecta o atributo ao binding 0
    glVertexArrayAttribBinding(ID, layout, 0);
    //define o formato do atributo dentro do buffer
    glVertexArrayAttribFormat(ID, layout, components, GL_FLOAT, GL_FALSE, offset);
}
