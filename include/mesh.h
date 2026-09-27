#ifndef MESH_H
#define MESH_H

#include <glad/gl.h>
#include <cstddef>

class Mesh {
    GLuint vbo = 0;
    GLuint vao = 0;
    size_t vertexCount = 0;

public:
    Mesh(const float* vertices, size_t size);

    Mesh(const Mesh& other) = delete;
    
    ~Mesh();

    Mesh& operator=(const Mesh& other) = delete;

    void render() const;
};

#endif