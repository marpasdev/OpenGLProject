/**
 * @file camera.h
 *
 * @brief Declaration of the Camera class.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/mat4x4.hpp>

class Camera {
    glm::mat4 view;
    glm::mat4 projection;

public:
    Camera(const glm::mat4& view, const glm::mat4& projection);

    void setView(const glm::mat4& newView);
    void setProjection(const glm::mat4& newProjection);

    glm::mat4 getView() const;
    glm::mat4 getProjection() const;

};

#endif // CAMERA_H