#include "../Header/VAOManager.h"


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

    float* verticesSkySphere, size_t skySphereSize, unsigned int& VAOskySphere,

    SphereMesh ballMesh, unsigned int& VAOball

) {




    //Pločica sa imenom
    unsigned int VBOnametag;
    glGenVertexArrays(1, &VAOnametag);
    glGenBuffers(1, &VBOnametag);

    glBindVertexArray(VAOnametag);
    glBindBuffer(GL_ARRAY_BUFFER, VBOnametag);
    glBufferData(GL_ARRAY_BUFFER, nametagSize, verticesNametag, GL_STATIC_DRAW);

    // Atribut 0 (pozicija):
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribut 1 (boja):
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Pozadina distance teksta
    unsigned int VBOdistanceBackground;
    glGenVertexArrays(1, &VAOdistanceBackground);
    glGenBuffers(1, &VBOdistanceBackground);

    glBindVertexArray(VAOdistanceBackground);
    glBindBuffer(GL_ARRAY_BUFFER, VBOdistanceBackground);
    glBufferData(GL_ARRAY_BUFFER, distanceBackgroundSize, verticesTopLeftRect, GL_STATIC_DRAW);

    // Atribut 0 (pozicija):
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribut 1 (boja):
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------- Mercury Icon --------------------
    unsigned int VBOmercuryIcon;
    glGenVertexArrays(1, &VAOmercuryIcon);
    glGenBuffers(1, &VBOmercuryIcon);

    glBindVertexArray(VAOmercuryIcon);
    glBindBuffer(GL_ARRAY_BUFFER, VBOmercuryIcon);
    glBufferData(GL_ARRAY_BUFFER, mercuryIconSize, verticesMercuryIcon, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------- Venus Icon --------------------
    unsigned int VBOvenusIcon;
    glGenVertexArrays(1, &VAOvenusIcon);
    glGenBuffers(1, &VBOvenusIcon);

    glBindVertexArray(VAOvenusIcon);
    glBindBuffer(GL_ARRAY_BUFFER, VBOvenusIcon);
    glBufferData(GL_ARRAY_BUFFER, venusIconSize, verticesVenusIcon, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------- Mars Icon --------------------
    unsigned int VBOmarsIcon;
    glGenVertexArrays(1, &VAOmarsIcon);
    glGenBuffers(1, &VBOmarsIcon);

    glBindVertexArray(VAOmarsIcon);
    glBindBuffer(GL_ARRAY_BUFFER, VBOmarsIcon);
    glBufferData(GL_ARRAY_BUFFER, marsIconSize, verticesMarsIcon, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------- Jupiter Icon --------------------
    unsigned int VBOjupiterIcon;
    glGenVertexArrays(1, &VAOjupiterIcon);
    glGenBuffers(1, &VBOjupiterIcon);

    glBindVertexArray(VAOjupiterIcon);
    glBindBuffer(GL_ARRAY_BUFFER, VBOjupiterIcon);
    glBufferData(GL_ARRAY_BUFFER, jupiterIconSize, verticesJupiterIcon, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------- Saturn Icon --------------------
    unsigned int VBOsaturnIcon;
    glGenVertexArrays(1, &VAOsaturnIcon);
    glGenBuffers(1, &VBOsaturnIcon);

    glBindVertexArray(VAOsaturnIcon);
    glBindBuffer(GL_ARRAY_BUFFER, VBOsaturnIcon);
    glBufferData(GL_ARRAY_BUFFER, saturnIconSize, verticesSaturnIcon, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------- Uranus Icon --------------------
    unsigned int VBOuranusIcon;
    glGenVertexArrays(1, &VAOuranusIcon);
    glGenBuffers(1, &VBOuranusIcon);

    glBindVertexArray(VAOuranusIcon);
    glBindBuffer(GL_ARRAY_BUFFER, VBOuranusIcon);
    glBufferData(GL_ARRAY_BUFFER, uranusIconSize, verticesUranusIcon, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------- Neptune Icon --------------------
    unsigned int VBOneptuneIcon;
    glGenVertexArrays(1, &VAOneptuneIcon);
    glGenBuffers(1, &VBOneptuneIcon);

    glBindVertexArray(VAOneptuneIcon);
    glBindBuffer(GL_ARRAY_BUFFER, VBOneptuneIcon);
    glBufferData(GL_ARRAY_BUFFER, neptuneIconSize, verticesNeptuneIcon, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // -------------------- Pluto Icon --------------------
    unsigned int VBOplutoIcon;
    glGenVertexArrays(1, &VAOplutoIcon);
    glGenBuffers(1, &VBOplutoIcon);

    glBindVertexArray(VAOplutoIcon);
    glBindBuffer(GL_ARRAY_BUFFER, VBOplutoIcon);
    glBufferData(GL_ARRAY_BUFFER, plutoIconSize, verticesPlutoIcon, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //-------------------SkySphere--------------------
    unsigned VBOskySphere;
    glGenVertexArrays(1, &VAOskySphere);
    glGenBuffers(1, &VBOskySphere);

    glBindVertexArray(VAOskySphere);
    glBindBuffer(GL_ARRAY_BUFFER, VBOskySphere);
    glBufferData(GL_ARRAY_BUFFER, skySphereSize, verticesSkySphere, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);


    // -------------------- Sphere --------------------
    unsigned int VBOball, EBOball;
    glGenVertexArrays(1, &VAOball);
    glGenBuffers(1, &VBOball);
    glGenBuffers(1, &EBOball);

    glBindVertexArray(VAOball);

    glBindBuffer(GL_ARRAY_BUFFER, VBOball);
    glBufferData(GL_ARRAY_BUFFER, ballMesh.vertices.size() * sizeof(float), ballMesh.vertices.data(), GL_STATIC_DRAW);

    // Pozicija
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Boja
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOball);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ballMesh.indices.size() * sizeof(unsigned int), ballMesh.indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);



}