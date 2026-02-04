#pragma once
#include <vector>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


// Nametag
extern float verticesNametag[16];

// Distance background
extern float verticesTopLeftRect[16];

extern float videoVertices[24];

//middle screen cross
std::vector<float> generateCrosshairVertices(float aspect);


// Sky sphere
std::vector<float> generateSphere(float radius = 0.2f, int sectorCount = 20, int stackCount = 20);

// Planet sphere
struct SphereMesh {
    std::vector<float> vertices;       // x, y, z, r, g, b, a, u, v
    std::vector<unsigned int> indices;
};

struct Planet {
    float x;
    float scale;
    unsigned int texture;
};
SphereMesh generateSphereTextured(float radius, int sectorCount, int stackCount);

//Saturn ring
struct RingMesh {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

RingMesh generateRing(
    float innerRadius,
    float outerRadius,
    int segments
);

SphereMesh generatePlanetTextured(float radius, int sectorCount, int stackCount);

