/**
 * @file camera.cpp
 *
 * @brief 
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

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
}

glm::vec3 Camera::getPosition() const {
    return eye;
}

void Camera::moveForward(float value) {
    center += glm::vec3(0.0f, 0.0f, 1.0f * value);
    eye += glm::vec3(0.0f, 0.0f, 1.0f * value);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
}

void Camera::moveBackward(float value) {
    center -= glm::vec3(0.0f, 0.0f, 1.0f * value);
    eye -= glm::vec3(0.0f, 0.0f, 1.0f * value);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
}

void Camera::moveRight(float value) {
    center += glm::vec3(value * 1.0f, 0.0f, 0.0f);
    eye += glm::vec3(1.0f * value, 0.0f, 0.0f);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
}

void Camera::moveLeft(float value) {
    center -= glm::vec3(1.0f * value, 0.0f, 0.0f);
    eye -= glm::vec3(1.0f * value, 0.0f, 0.0f);
    view = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::scale(view, glm::vec3(-1.0f, 1.0f, 1.0f));
}

void Camera::moveUp(float value) {

}

void Camera::moveDown(float value) {

}