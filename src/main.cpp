#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include "Shader.h"
#include "Sphere.h"
#include "Camera.h"
#include "Planet.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>  // Funciones como glm::rotate, glm::translate, glm::perspective
#include <glm/gtc/type_ptr.hpp>  
// Triángulo simple
float vertices[] = {
    0.0f,
    0.5f,
    0.0f,
    -0.7f,
    -0.7f,
    0.1f,
    0.5f,
    -0.5f,
    0.0f,
};

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Solar System", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Configurar viewport y depth test
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    // VBO + VAO
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Shader
    Shader shader("../shaders/vertex.vert", "../shaders/fragment.frag");

    // Charge the objects
    Sphere sphere(1.0f, 36, 18);
    Camera camera(
        glm::vec3(0.0f, 0.0f, 3.0f), // posición
        45.0f,                       // FOV
        800.0f / 600.0f,             // aspect ratio
        0.1f,                        // near
        100.0f                       // far
    );
    //Solar system
    Planet sun(1.0f, 0.0f, 0.0f, 0.5f, glm::vec3(1.0f, 1.0f, 0.0f));
    Planet earth(0.3f, 3.0f, 0.5f, 1.0f, glm::vec3(0.0f, 0.3f, 1.0f));
    

    // Loop
    while (!glfwWindowShouldClose(window))
    {
        float deltaTime = 0.005f;
        // glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix();
        glm::mat4 model = glm::mat4(1.0f); // matriz identidad
        // model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);
        sun.update(deltaTime);
        earth.update(deltaTime);

        sun.draw(shader);
        earth.draw(shader);
        // sphere.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }

    glfwTerminate();
    return 0;
}
