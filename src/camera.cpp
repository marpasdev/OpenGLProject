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
#include <glm/common.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>

#include <algorithm>

Camera::Camera(const glm::vec3& pos)
: eye(pos) {
    front = eye + glm::vec3(0.0f, 0.0f, 1.0f);
    view = glm::lookAt(eye, front, glm::vec3(0.0f, 1.0f, 0.0f));
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

void Camera::updateView() {
    front = glm::normalize(glm::vec3(
        cos(yaw) * cos(pitch),
        sin(pitch),
        sin(yaw) * cos(pitch)
    ));

    view = glm::lookAt(eye, eye + front, up);
    view = glm::scale(view, glm::vec3{-1.0f, 1.0f, 1.0f});
    notify();
}

void Camera::rotate(float deltaYaw, float deltaPitch) {
    yaw += deltaYaw;
    pitch = glm::clamp(pitch + deltaPitch, glm::radians(-89.0f), glm::radians(89.0f));
    updateView();
}

void Camera::moveForward(float value) {
    eye += front * value;
    updateView();
}

void Camera::moveBackward(float value) {
    eye -= front * value;
    updateView();
}

void Camera::moveRight(float value) {
    eye += glm::normalize(glm::cross(front, up)) * value;
    updateView();
}

void Camera::moveLeft(float value) {
    eye -= glm::normalize(glm::cross(front, up)) * value;
    updateView();
}

void Camera::moveUp(float value) {
    eye += up * value;
    updateView();
}

void Camera::moveDown(float value) {
    eye -= up * value;
    updateView();
}