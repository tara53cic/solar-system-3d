#pragma once
#include <GLFW/glfw3.h>
#include "../Header/Collision.h"

#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern float yaw;
extern float pitch;
extern bool firstMouse;
extern float lastX;
extern float lastY;
extern float simDistanceTravelled;
extern glm::vec3 lastCameraPos;
extern float fov;
extern bool ENABLE_DEPTH_TEST;
extern bool ENABLE_CULL_FACE;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void processInput(GLFWwindow* window, float deltaTime, float distanceFactor);

#pragma once
