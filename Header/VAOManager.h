#pragma once
#include <GL/glew.h>
#include "Vertices.h"

void formVAOs(

    // Nametag
    float* verticesNametag, size_t nametagSize, unsigned int& VAOnametag,

    // Distance background
    float* verticesTopLeftRect, size_t distanceBackgroundSize, unsigned int& VAOdistanceBackground,


    // Pluto icon
    float* verticesPlutoIcon, size_t plutoIconSize, unsigned int& VAOplutoIcon,

    // Mercury icon
    float* verticesMercuryIcon, size_t mercuryIconSize, unsigned int& VAOmercuryIcon,

    // Venus icon
    float* verticesVenusIcon, size_t venusIconSize, unsigned int& VAOvenusIcon,

    // Mars icon
    float* verticesMarsIcon, size_t marsIconSize, unsigned int& VAOmarsIcon,

    // Jupiter icon
    float* verticesJupiterIcon, size_t jupiterIconSize, unsigned int& VAOjupiterIcon,

    // Saturn icon
    float* verticesSaturnIcon, size_t saturnIconSize, unsigned int& VAOsaturnIcon,

    // Uranus icon
    float* verticesUranusIcon, size_t uranusIconSize, unsigned int& VAOuranusIcon,

    // Neptune icon
    float* verticesNeptuneIcon, size_t neptuneIconSize, unsigned int& VAOneptuneIcon,

    //Pozadina, sfera
    SphereMesh skySphereMesh, unsigned int& VAOskySphere,

    //Planetarna sfera
    SphereMesh ballMesh, unsigned int& VAOball,

    RingMesh ringMesh, unsigned int& VAOring,
    float* verticesCrosshair, size_t verticesCrosshairSize, unsigned int& VAOcrosshair
);
