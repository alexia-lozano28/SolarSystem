#include "Sphere.h"
#include <OpenGL/gl3.h> // Core Profile Mac Intel
#include <cmath>


Sphere::Sphere(float radius, int stacks, int sectors)
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    const float PI = 3.1415926f;

    // === Generar vértices ===
    for (int i = 0; i <= stacks; ++i)
    {
        float phi = -PI / 2.0f + i * (PI / stacks);
        float y = radius * sin(phi);
        float r = radius * cos(phi);

        for (int j = 0; j <= sectors; ++j)
        {
            float theta = j * (2.0f * PI / sectors);

            float x = r * cos(theta);
            float z = r * sin(theta);

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    // === Generar índices (triángulos) ===
    for (int i = 0; i < stacks; ++i)
    {
        for (int j = 0; j < sectors; ++j)
        {
            int first  = i * (sectors + 1) + j;
            int second = first + sectors + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    indexCount = indices.size();

    // === Crear buffers OpenGL ===
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(float),
                 vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int),
                 indices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Sphere::draw()
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount,
                   GL_UNSIGNED_INT, 0);
}