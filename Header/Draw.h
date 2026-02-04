#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <cmath> 
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vertices.h"
#include "AlienModel.h"



void drawBackground(unsigned int shader, unsigned int vao, unsigned int tex);
void drawNametag(unsigned int shader, unsigned int vao, unsigned int tex);
void drawDistanceBackground(unsigned int shader, unsigned int vao, unsigned int tex);
void drawAlienIcon(unsigned int alienIconShader, unsigned int VAOalienIcon, unsigned int alienIconTexture);
void drawHelp(unsigned int shader, unsigned int vao, unsigned int tex);
void drawSkySphere(
    unsigned int skysphereShader,
    unsigned int VAOskySphere,
    unsigned int skysphereTexture,
    const SphereMesh& skySphereMesh,
    glm::mat4 projection,
    glm::mat4 view
);
void drawSphere(unsigned int unifiedShader,
    unsigned int VAOball,
    unsigned int planetTexture,
    const SphereMesh& ballMesh,
    const glm::mat4& model,
    const glm::mat4& projection,
    const glm::mat4& view);

void drawPlanetWithLighting(
    unsigned int planetShader,
    unsigned int VAOball,
    unsigned int planetTexture,
    const SphereMesh& ballMesh,
    const glm::mat4& model,
    const glm::mat4& projection,
    const glm::mat4& view,
    const glm::vec3& sunPos,
    const glm::vec3& cameraPos
);

void drawRing(
    unsigned int unifiedShader,
    unsigned int VAOring,
    unsigned int ringTexture,
    const RingMesh& ringMesh,
    const glm::mat4& model,
    const glm::mat4& projection,
    const glm::mat4& view
);
void drawAlien(unsigned int alienShader, AlienModel& alien, const glm::mat4& model,
    const glm::mat4& projection, const glm::mat4& view, glm::vec3 cameraPos);

void drawAlienStationary(
    unsigned int alienShader,
    AlienModel& alien,
    const glm::mat4& model,
    const glm::mat4& projection,
    const glm::mat4& view,
    const glm::vec3& cameraPos,
    const glm::vec3& worldPos
);
#pragma once
