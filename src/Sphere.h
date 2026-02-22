#ifndef SPHERE_H
#define SPHERE_H

#include <vector>

class Sphere {
public:
    unsigned int ID;

    Sphere( float radius,int stacks, int sectors);
    void draw();

private:
    unsigned int VAO, VBO, EBO;
    unsigned int indexCount;
};

#endif
