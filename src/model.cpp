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

#include <glad/gl.h>

#include <exception>
#include <iostream>
#include <cstdlib>

#include "model.h"

Model::Model(const float* vertices, size_t size, const std::vector<VertexAttribute>& attributes) {
    size_t vertexDataSize = 0;

    for (const auto& attrib : attributes) {
        size_t componentSize = 0;
        switch (attrib.type) {
            case GL_INT:
                componentSize = sizeof(GLint);
                break;
            case GL_FLOAT:
                componentSize = sizeof(GLfloat);
                break;
            case GL_DOUBLE:
                componentSize = sizeof(GLdouble);
                break;
            default:
                std::cerr << "Unsupported OpenGL type given as vertex attribute.\n";
                exit(EXIT_FAILURE);
        }
        vertexDataSize += componentSize * attrib.componentCount;
    }

    vertexCount = size / vertexDataSize;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    for (size_t i = 0; i < attributes.size(); ++i) {
        glEnableVertexAttribArray(static_cast<GLuint>(i));
    }

    size_t offset = 0;
    for (size_t i = 0; i < attributes.size(); ++i) {
        const auto& attrib = attributes[i];
        size_t componentSize = 0;

        switch (attrib.type) {
            case GL_INT:
                glVertexAttribIPointer(i, attrib.componentCount, attrib.type, vertexDataSize, (GLvoid*)offset);
                componentSize = sizeof(GLint);
                break;
            case GL_FLOAT:
                glVertexAttribPointer(i, attrib.componentCount, attrib.type, GL_FALSE, vertexDataSize, (GLvoid*)offset);
                componentSize = sizeof(GLfloat);
                break;
            case GL_DOUBLE:
                glVertexAttribLPointer(i, attrib.componentCount, attrib.type, vertexDataSize, (GLvoid*)offset);
                componentSize = sizeof(GLdouble);
                break;
            default:
                std::cerr << "Unsupported OpenGL type given as vertex attribute.\n";
                exit(EXIT_FAILURE);
        }

        offset += attrib.componentCount * componentSize;
    }
}

Model::~Model() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Model::render() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}