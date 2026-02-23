#ifndef PLANET_H
#define PLANET_H

#include "Sphere.h"
#include "Shader.h"
#include <glm/glm.hpp>

class Planet
{
public:
    Planet(float radius, float orbitRadius, float orbitSpeed, float rotationSpeed, const char* texturePath ); // constructor

    void draw(Shader& shader);
    void update(float deltaTime);

    float currentOrbitAngle;
    float currentRotationAngle;

private:
    float radius;
    float orbitRadius;
    float rotationSpeed;
    float orbitSpeed;
    glm::vec3 color;

    Sphere sphere;
    unsigned int textureID;
};

#endif