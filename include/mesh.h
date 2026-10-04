/**
 * @file mesh.h
 *
 * @brief Declaration of the Mesh class, which is a wrapper over VAO and VBO.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

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

#endif // MESH_H