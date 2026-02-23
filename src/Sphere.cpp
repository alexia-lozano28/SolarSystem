#define GL_SILENCE_DEPRECATION
#include "Sphere.h"
#include <cmath>
#include <iostream>
#include <OpenGL/gl3.h>

Sphere::Sphere(float radius, unsigned int longitudeSegments, unsigned int latitudeSegments)
{
    for (unsigned int y = 0; y <= latitudeSegments; y++)
    {
        for (unsigned int x = 0; x <= longitudeSegments; x++)
        {
            float xSegment = (float)x / longitudeSegments;
            float ySegment = (float)y / latitudeSegments;
            float xPos = radius * std::cos(xSegment * 2.0f * 3.141516f) * std::sin(ySegment * 3.141516f);
            float yPos = radius * std::cos(ySegment * 3.141516f);
            float zPos = radius * std::sin(xSegment * 2.0f * 3.141516f) * std::sin(ySegment * 3.141516f);

            Vertex vertex;
            vertex.Position = glm::vec3(xPos, yPos, zPos);
            vertex.Normal = glm::normalize(vertex.Position);
            vertex.TexCoords = glm::vec2(xSegment, ySegment);
            vertices.push_back(vertex);
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < latitudeSegments; y++)
    {
        for (unsigned int x = 0; x < longitudeSegments; x++)
        {
            indices.push_back(y * (longitudeSegments + 1) + x);
            indices.push_back((y + 1) * (longitudeSegments + 1) + x);
            indices.push_back((y + 1) * (longitudeSegments + 1) + x + 1);

            indices.push_back(y * (longitudeSegments + 1) + x);
            indices.push_back((y + 1) * (longitudeSegments + 1) + x + 1);
            indices.push_back(y * (longitudeSegments + 1) + x + 1);
        }
    }

    setupSphere();
}

void Sphere::setupSphere()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Sphere::draw() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}