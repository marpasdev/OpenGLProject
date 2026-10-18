/**
 * @file camera.cpp
 *
 * @brief Represents a camera, having a way to notify its observers.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "camera.h"
#include "cameraobserver.h"

#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

Camera::Camera(const glm::vec3& pos)
: eye(pos) {
    center = eye + glm::vec3(0.0f, 0.0f, 1.0f);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
    projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 100.0f);
}

glm::mat4 Camera::getView() const {
    return view;
}

glm::mat4 Camera::getProjection() const {
    return projection;
}

void Camera::setProjection(const glm::mat4& newProjection) {
    projection = newProjection;
    notify();
}

glm::vec3 Camera::getPosition() const {
    return eye;
}

void Camera::attach(CameraObserver* o) {
    observers.push_back(o);
    o->onCameraChanged(*this);
}

void Camera::detach(CameraObserver* o) {
    observers.erase(std::remove(observers.begin(), observers.end(), o), observers.end());
}

void Camera::notify() const {
    auto copy = observers;
    for (auto* o : copy) {
        o->onCameraChanged(*this);
    }
}

void Camera::moveForward(float value) {
    center += glm::vec3(0.0f, 0.0f, 1.0f * value);
    eye += glm::vec3(0.0f, 0.0f, 1.0f * value);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
    notify();
}

void Camera::moveBackward(float value) {
    center -= glm::vec3(0.0f, 0.0f, 1.0f * value);
    eye -= glm::vec3(0.0f, 0.0f, 1.0f * value);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
    notify();
}

void Camera::moveRight(float value) {
    center += glm::vec3(value * -1.0f, 0.0f, 0.0f);
    eye += glm::vec3(-1.0f * value, 0.0f, 0.0f);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
    notify();
}

void Camera::moveLeft(float value) {
    center -= glm::vec3(-1.0f * value, 0.0f, 0.0f);
    eye -= glm::vec3(-1.0f * value, 0.0f, 0.0f);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
    notify();
}

void Camera::moveUp(float value) {
    center += glm::vec3(0.0f, 1.0f * value, 0.0f);
    eye += glm::vec3(0.0f, 1.0f * value, 0.0f);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
    notify();
}

void Camera::moveDown(float value) {
    center -= glm::vec3(0.0f, value * 1.0f, 0.0f);
    eye -= glm::vec3(0.0f, value * 1.0f, 0.0f);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
    notify();
}