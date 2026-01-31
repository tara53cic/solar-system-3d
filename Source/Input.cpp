#include "../Header/Input.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// Globals
const float BASE_INTERACT_DISTANCE = 0.3f;
const float INTERACT_RADIUS_MULT = 2.0f; 

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float yaw = -90.0f;
float pitch = 0.0f;
bool firstMouse = true;
float lastX = 0.0f;
float lastY = 0.0f;
float fov = 45.0f;

float simDistanceTravelled = 0.0f;
glm::vec3 lastCameraPos = cameraPos;

bool ENABLE_DEPTH_TEST = true;
bool ENABLE_CULL_FACE = false;


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 45.0f) fov = 45.0f;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //Depth i Cull Face
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_P:
            ENABLE_DEPTH_TEST = !ENABLE_DEPTH_TEST;
            if (ENABLE_DEPTH_TEST)
                glEnable(GL_DEPTH_TEST);
            else
                glDisable(GL_DEPTH_TEST);
            std::cout << "[INFO] Depth Test " << (ENABLE_DEPTH_TEST ? "ENABLED" : "DISABLED") << "\n";
            break;
        case GLFW_KEY_O: 
            ENABLE_CULL_FACE = !ENABLE_CULL_FACE;
            if (ENABLE_CULL_FACE) {
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);
                glFrontFace(GL_CCW);
            }
            else
                glDisable(GL_CULL_FACE);
            std::cout << "[INFO] Cull Face " << (ENABLE_CULL_FACE ? "ENABLED" : "DISABLED") << "\n";
            break;
        }
    }
}

void processInput(GLFWwindow* window, float deltaTime, float distanceFactor, const std::vector<Planet>& planets, int& state) {
    // ESC za zatvaranje prozora
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // brzina kamere
    float cameraSpeedSim = 1.0f; 
    float frameDistance = 0.0f;

    //jesmo pritisnuli ENTER?
    static bool enterPressedLastFrame = false;
    bool enterPressedNow = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;

    //jesmo pritisnuli Q
    static bool QPressedLastFrame = false;
    bool QPressedNow = glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS;

    //WASD + SPACE + SHIFT za kretanje kamere
    if (state == 0) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeedSim * cameraFront * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeedSim * cameraFront * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeedSim * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeedSim * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            cameraPos += cameraUp * cameraSpeedSim * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            cameraPos -= cameraUp * cameraSpeedSim * deltaTime;

        // Update distance only when moving
        frameDistance = glm::length(cameraPos - lastCameraPos);
        simDistanceTravelled += frameDistance;
        lastCameraPos = cameraPos;
    }

    if (enterPressedNow && !enterPressedLastFrame) {

        for (size_t i = 1; i < planets.size(); i++) {

            glm::vec3 planetPos(planets[i].x, 0.0f, 0.0f);

            float distanceToPlanet = glm::length(cameraPos - planetPos);

            float planetRadius = planets[i].scale;

            float interactDistance =
                BASE_INTERACT_DISTANCE + planetRadius * INTERACT_RADIUS_MULT;

            if (distanceToPlanet <= interactDistance) {

                state = static_cast<int>(i);

                std::cout << "[STATE] Changed to " << state
                    << " (planet " << i
                    << ", interactDist=" << interactDistance << ")\n";

                break;
            }
        }

    }

    if (state!=0 && QPressedNow && !QPressedLastFrame) {


                state = static_cast<int>(0);

                std::cout << "[STATE] Changed to 0" << state
                    << "\n";

    }


}
