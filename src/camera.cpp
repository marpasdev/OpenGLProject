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

Camera::Camera(const glm::mat4& view, const glm::mat4& projection)
    : view(view), projection(projection) {}

glm::mat4 Camera::getView() const {
    return view;
}

glm::mat4 Camera::getProjection() const {
    return projection;
}

void Camera::setView(const glm::mat4& newView) {
    view = newView;
}

void Camera::setProjection(const glm::mat4& newProjection) {
    projection = newProjection;
}