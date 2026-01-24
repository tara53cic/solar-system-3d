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



//Alien icons
extern float verticesMercuryIcon[16];
extern float verticesVenusIcon[16];
extern float verticesMarsIcon[16];
extern float verticesJupiterIcon[16];
extern float verticesSaturnIcon[16];
extern float verticesUranusIcon[16];
extern float verticesNeptuneIcon[16];
extern float verticesPlutoIcon[16];


// Sky sphere
std::vector<float> generateSphere(float radius = 0.2f, int sectorCount = 20, int stackCount = 20);

// Planet sphere
struct SphereMesh {
    std::vector<float> vertices;       // x, y, z, r, g, b, a, u, v
    std::vector<unsigned int> indices;
};
SphereMesh generateSphereTextured(float radius, int sectorCount, int stackCount);

