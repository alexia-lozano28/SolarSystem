#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float yaw;  
    float pitch; 
    float movementSpeed;
    float mouseSensitivity; 
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    
    float velocity;

    Camera(glm::vec3 position);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix() const;

    void processKeyboard(GLFWwindow* window, float deltaTime);
    void processMouse(float xoffset, float yoffset); // mover cámara con teclado
private:
    void updateCameraVectors();
};

#endif