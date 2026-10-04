/**
 * @file mesh.h
 *
 * @brief Declaration of the Model class, which is a wrapper over VAO and VBO.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef MODEL_H
#define MODEL_H

#include <glad/gl.h>
#include <cstddef>

class Model {
    GLuint vbo = 0;
    GLuint vao = 0;
    size_t vertexCount = 0;

public:
    Model(const float* vertices, size_t size);

    Model(const Model& other) = delete;
    
    ~Model();

    Model& operator=(const Model& other) = delete;

    void render() const;
};

#endif // MODEL_H