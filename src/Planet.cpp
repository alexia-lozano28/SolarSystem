#define GL_SILENCE_DEPRECATION

#include "Planet.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "stb_image.h"
// Constructor
Planet::Planet(float radius, float orbitRadius, float orbitSpeed, float rotationSpeed, const char *texturePath)
    : sphere(radius, 36, 18),
      radius(radius),
      orbitRadius(orbitRadius),
      orbitSpeed(orbitSpeed),
      rotationSpeed(rotationSpeed),
      currentOrbitAngle(0.0f),
      currentRotationAngle(0.0f)
{
    // --- Load texture ---
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
    stbi_image_free(data);
}

void Planet::update(float deltaTime)
{
    currentOrbitAngle += orbitSpeed * deltaTime;
    currentRotationAngle += rotationSpeed * deltaTime;
}

void Planet::draw(Shader &shader)
{
    shader.use();

    glm::mat4 model(1.0f);
    model = glm::rotate(model, currentOrbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(orbitRadius, 0.0f, 0.0f));
    model = glm::rotate(model, currentRotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(radius));

    shader.setMat4("model", model);

    // --- Bind texture ---
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shader.setInt("planetTexture", 0);

    sphere.draw();
}