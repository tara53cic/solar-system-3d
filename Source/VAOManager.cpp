#include "../Header/VAOManager.h"


void formVAOs(

    // Nametag
    float* verticesNametag, size_t nametagSize, unsigned int& VAOnametag,

    // Distance background
    float* verticesTopLeftRect, size_t distanceBackgroundSize, unsigned int& VAOdistanceBackground,

    SphereMesh skySphereMesh, unsigned int& VAOskySphere,

    SphereMesh ballMesh, unsigned int& VAOball,

    RingMesh ringMesh, unsigned int& VAOring,
    float* verticesCrosshair, size_t verticesCrosshairSize, unsigned int& VAOcrosshair,

    float* videoVertices, unsigned int& videoVAO

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


    // -------------------- Sky Sphere --------------------
    unsigned int VBOsky, EBOsky;
    glGenVertexArrays(1, &VAOskySphere);
    glGenBuffers(1, &VBOsky);
    glGenBuffers(1, &EBOsky);

    glBindVertexArray(VAOskySphere);

    glBindBuffer(GL_ARRAY_BUFFER, VBOsky);
    glBufferData(
        GL_ARRAY_BUFFER,
        skySphereMesh.vertices.size() * sizeof(float),
        skySphereMesh.vertices.data(),
        GL_STATIC_DRAW
    );

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color (unused but harmless)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // UV (unused but harmless)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOsky);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        skySphereMesh.indices.size() * sizeof(unsigned int),
        skySphereMesh.indices.data(),
        GL_STATIC_DRAW
    );

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


    // -------------------- Saturn ring --------------------
    unsigned int VBOring, EBOring;
    glGenVertexArrays(1, &VAOring);
    glGenBuffers(1, &VBOring);
    glGenBuffers(1, &EBOring);

    glBindVertexArray(VAOring);

    glBindBuffer(GL_ARRAY_BUFFER, VBOring);
    glBufferData(GL_ARRAY_BUFFER, ringMesh.vertices.size() * sizeof(float), ringMesh.vertices.data(), GL_STATIC_DRAW);

    // Pozicija
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Boja
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOring);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ringMesh.indices.size() * sizeof(unsigned int), ringMesh.indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

    // -------------------- Crosshair --------------------
    unsigned int VBOcrosshair;
    glGenVertexArrays(1, &VAOcrosshair);
    glGenBuffers(1, &VBOcrosshair);

    glBindVertexArray(VAOcrosshair);
    glBindBuffer(GL_ARRAY_BUFFER, VBOcrosshair);
    glBufferData(GL_ARRAY_BUFFER, verticesCrosshairSize, verticesCrosshair, GL_STATIC_DRAW);

    // Atribut 0 (pozicija):
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Atribut 1 (boja):
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //video overlay

    unsigned int videoVBO;
    glGenVertexArrays(1, &videoVAO);
    glGenBuffers(1, &videoVBO);
    glBindVertexArray(videoVAO);
    glBindBuffer(GL_ARRAY_BUFFER, videoVBO);

    // 6 vertices * 4 components (x, y, u, v) * 4 bytes
    glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), videoVertices, GL_STATIC_DRAW);

    // Position attribute (Location 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // TexCoord attribute (Location 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


}