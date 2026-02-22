#define GL_SILENCE_DEPRECATION

#include "Planet.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Constructor (muy recomendable que lo añadas en el .h también)
Planet::Planet(float radius,
               float orbitRadius,
               float orbitSpeed,
               float rotationSpeed,
               glm::vec3 color)
    : sphere(radius, 36, 18),
      radius(radius),
      orbitRadius(orbitRadius),
      orbitSpeed(orbitSpeed),
      rotationSpeed(rotationSpeed),
      color(color),
      currentOrbitAngle(0.0f),
      currentRotationAngle(0.0f)
{
}

void Planet::update(float deltaTime)
{
    currentOrbitAngle += orbitSpeed * deltaTime;
    currentRotationAngle += rotationSpeed * deltaTime;
}

void Planet::draw(Shader& shader)
{
    glm::mat4 model = glm::mat4(1.0f);

    // 1️⃣ Rotación alrededor del origen (órbita)
    model = glm::rotate(model, currentOrbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));

    // 2️⃣ Trasladar hacia afuera (radio de órbita)
    model = glm::translate(model, glm::vec3(orbitRadius, 0.0f, 0.0f));

    // 3️⃣ Rotación sobre su propio eje
    model = glm::rotate(model, currentRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

    // 4️⃣ Escalar según su tamaño
    model = glm::scale(model, glm::vec3(radius));

    shader.setMat4("model", model);

    sphere.draw();
}