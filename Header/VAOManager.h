#pragma once
#include <GL/glew.h>
#include "Vertices.h"

void formVAOs(

    // Nametag
    float* verticesNametag, size_t nametagSize, unsigned int& VAOnametag,

    // Distance background
    float* verticesTopLeftRect, size_t distanceBackgroundSize, unsigned int& VAOdistanceBackground,

    //Pozadina, sfera
    SphereMesh skySphereMesh, unsigned int& VAOskySphere,

    //Planetarna sfera
    SphereMesh ballMesh, unsigned int& VAOball,
    SphereMesh planetMesh, unsigned int& VAOplanet,

    RingMesh ringMesh, unsigned int& VAOring,
    float* verticesCrosshair, size_t verticesCrosshairSize, unsigned int& VAOcrosshair,
    float* videoVertices, unsigned int& videoVAO
);
