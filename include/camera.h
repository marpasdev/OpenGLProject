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
#include <vector>

class CameraObserver;

class Camera {
    glm::mat4 view;
    glm::mat4 projection;

    glm::vec3 eye;
    glm::vec3 center;

    std::vector<CameraObserver*> observers;

    void notify() const;

public:
    Camera(const glm::vec3& eye);

    void setProjection(const glm::mat4& newProjection);

    glm::mat4 getView() const;
    glm::mat4 getProjection() const;

    glm::vec3 getPosition() const;

    void attach(CameraObserver* o);
    void detach(CameraObserver* o);

    void moveForward(float value);
    void moveBackward(float value);
    void moveRight(float value);
    void moveLeft(float value);
    void moveUp(float value);
    void moveDown(float value);

    void rotateRight(float angle);
    void rotateLeft(float angle);
    void rotateUp(float angle);
    void rotateDown(float angle);
};

#endif // CAMERA_H