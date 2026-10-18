/**
 * @file cameraobserver.h
 *
 * @brief Declaration of the CameraObserver class, which is a base class for observers observing a camera's state.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef CAMERAOBSERVER_H
#define CAMERAOBSERVER_H

class Camera;

class CameraObserver {
public:
    virtual ~CameraObserver() = default;
    virtual void onCameraChanged(const Camera& camera) = 0;
};

#endif // CAMERAOBSERVER_H