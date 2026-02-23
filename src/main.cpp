#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "Sphere.h"
#include "Camera.h"
#include "Planet.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int SCR_WIDTH = 1280;
int SCR_HEIGHT = 720;

// -------------------
// Variables globales para el ratón
// -------------------
Camera camera(glm::vec3(0.0f, 0.0f, 20.0f));
float lastX = SCR_WIDTH;
float lastY = SCR_HEIGHT;
bool firstMouse = true;

// -------------------
// Callback ratón
// -------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.processMouse(xoffset, yoffset);
}

// -------------------

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

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Solar System", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Capturar ratón tipo FPS
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    Shader shader("../shaders/planet.vert", "../shaders/planet.frag");

    // ------------------- PLANETAS -------------------

    struct PlanetData
    {
        float radius;
        float orbitRadius;
        float orbitSpeed;
        float rotationSpeed;
        const char *texture;
    };

    std::vector<PlanetData> planetInfo = {
        {0.2f, 4.0f, 0.05f, 0.5f, "../assets/textures/mercury.jpeg"},
        {0.3f, 6.0f, 0.05f, 0.5f, "../assets/textures/venus.jpeg"},
        {0.35f, 8.0f, 0.05f, 0.5f, "../assets/textures/earth.jpeg"},
        {0.25f, 10.0f, 0.05f, 0.5f, "../assets/textures/mars.jpeg"},
        {1.0f, 14.0f, 0.02f, 1.0f, "../assets/textures/jupiter.jpg"},
        {0.8f, 18.0f, 0.015f, 1.0f, "../assets/textures/saturn.jpeg"},
        {0.6f, 22.0f, 0.01f, 1.0f, "../assets/textures/uranus.jpeg"},
        {0.6f, 26.0f, 0.008f, 1.0f, "../assets/textures/neptune.jpg"}};

    std::vector<Planet> solarSystem;
    Planet sun(2.0f, 0.0f, 0.0f, 0.5f, "../assets/textures/sun.jpeg");
    for (const auto &p : planetInfo)
    {
        solarSystem.emplace_back(
            p.radius,
            p.orbitRadius,
            p.orbitSpeed,
            p.rotationSpeed,
            p.texture);
    }

    float lastFrame = glfwGetTime();

    // ------------------- LOOP -------------------

    std::cout << "Pos: "
              << camera.position.x << " "
              << camera.position.y << " "
              << camera.position.z << std::endl;

    std::cout << "Front: "
              << camera.front.x << " "
              << camera.front.y << " "
              << camera.front.z << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.processKeyboard(window, deltaTime);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // View
        glm::mat4 view = camera.getViewMatrix();
        // glm::mat4 view = glm::lookAt(
        //     glm::vec3(0.0f, 0.0f, 30.0f),
        //     glm::vec3(0.0f, 0.0f, 0.0f),
        //     glm::vec3(0.0f, 1.0f, 0.0f));

        // glm::mat4 projection = camera.getProjectionMatrix();
        // Projection
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glm::mat4 projection = glm::perspective(
            glm::radians(camera.fov),
            (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f,
            5000.0f);
        
        glm::vec3 sunPosition(0.0f,0.0f,0.0f);
        shader.setVec3("lightPos", sunPosition);
        shader.setVec3("viewPos", camera.position);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setBool("isSun", true);
        sun.update(deltaTime);
        sun.draw(shader);
        shader.setBool("isSun", false);
        // Dibujar planetas
        for (auto &p : solarSystem)
        {
            p.update(deltaTime);
            p.draw(shader);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}