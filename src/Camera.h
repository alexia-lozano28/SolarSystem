#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <glm/glm.hpp>


class Camera {
public:
    Camera(glm::vec3 position, float fov, float aspectRatio, float nearPlane, float farPlane);
    
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
};

#endif
