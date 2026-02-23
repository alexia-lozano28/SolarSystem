#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;   // posición del vértice
    glm::vec3 Normal;     // normal para iluminación
    glm::vec2 TexCoords;  // coordenadas de textura
};

class Sphere
{
public:
    // Constructor: radio, segmentos de longitud y latitud
    Sphere(float radius = 1.0f, unsigned int longitudeSegments = 36, unsigned int latitudeSegments = 18);

    // Dibujar la esfera
    void draw() const;

private:
    std::vector<Vertex> vertices;        // lista de vértices
    std::vector<unsigned int> indices;   // lista de índices para glDrawElements

    unsigned int VAO, VBO, EBO;          // OpenGL buffers

    // Configura VAO, VBO, EBO
    void setupSphere();
};

#endif
