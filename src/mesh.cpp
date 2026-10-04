/**
 * @file mesh.cpp
 *
 * @brief A wrapper over VAO and VBO.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "mesh.h"

Mesh::Mesh(const float* vertices, size_t size) {
    vertexCount = size / (6 * sizeof(float));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Mesh::render() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}