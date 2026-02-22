#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <OpenGL/gl3.h> // Opcional si usas GLAD; en Mac Intel puedes probar <OpenGL/gl3.h>
#include <glm/glm.hpp>
class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void setMat4(const std::string& name, const glm::mat4& matrix) const;
    void use() const;
};

#endif
