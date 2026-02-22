#ifndef PLANET_H
#define PLANET_H

#include "Sphere.h"
#include "Shader.h"
#include <glm/glm.hpp>

class Planet
{
public:
    Planet(float radius, float orbitRadius, float orbitSpeed, float rotationSpeed, glm::vec3 color);
    Sphere sphere;
    void draw(Shader& Shader);
    void update(float timeDelta);
    float currentOrbitAngle;

    float currentRotationAngle;
private:
    float radius;
    float orbitRadius;
    float rotationSpeed;
    float orbitSpeed;
    glm::vec3 color;

};

#endif