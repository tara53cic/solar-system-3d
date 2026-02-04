#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Header/Util.h"
#include "../Header/TextRenderer.h"
#include "../Header/Vertices.h"
#include "../Header/VAOManager.h"
#include "../Header/Input.h"
#include "../Header/Draw.h"
#include "../Header/Shaders.h"
#include "../Header/stb_image.h"
#include "../Header/AlienModel.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <chrono>

// ------------------------------- GLOBAL VARIABLES -------------------------------

int state = 0;

// --- ALIEN STATE ---
bool mercuryCaught = false;
bool venusCaught = false;
bool marsCaught = false;
bool jupiterCaught = false;
bool saturnCaught = false;
bool uranusCaught = false;
bool neptuneCaught = false;
bool plutoCaught = false;

//---PLANETS ---

unsigned sunTexture, mercuryTexture, venusTexture, earthTexture,
	marsTexture, jupiterTexture, saturnTexture,
	uranusTexture, neptuneTexture, plutoTexture,saturnRingTexture;


//Planets-skies

unsigned mercurySkyTexture, venusSkyTexture, marsSkyTexture,
	jupiterSkyTexture, saturnSkyTexture,
	uranusSkyTexture, neptuneSkyTexture, plutoSkyTexture;
unsigned earthSkyTexture;

unsigned windowTexture, dashboardTexture, distanceCoverTexture;

unsigned wasdTexture, takeoffTexture, nametagTexture, goalTexture, onboardTexture, missionAccomplishedTexture, missionFailedTexture;

extern bool hasMovedAtAll;
extern bool isNearPlanet;


// ------------------------------- HELPER FUNCTIONS -------------------------------
void preprocessTexture(unsigned& texture, const char* filepath) {
    texture = loadImageToTexture(filepath);
    glBindTexture(GL_TEXTURE_2D, texture);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// ------------------------------- MAIN FUNCTION -------------------------------
int main() {
    // ---------------- GLFW INIT ----------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor* mon = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(mon);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Solar System", mon, nullptr);
    if (!window) return -1;
    glfwMakeContextCurrent(window);

    // --- Mouse and scroll ---
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    // ---------------- GLEW ----------------
    if (glewInit() != GLEW_OK) return -1;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);

    // ---------------- TEXT RENDERER ----------------
    TextRenderer textRenderer(mode->width, mode->height);
    textRenderer.Load("Resources/ScienceGothic_Condensed-Regular.ttf", 32);

    //depth testing and cull testing

    if (ENABLE_DEPTH_TEST) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }

    if (ENABLE_CULL_FACE) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }
    else {
        glDisable(GL_CULL_FACE);
    }


    // ---------------- TEXTURES ----------------
    unsigned mercuryIconCaught, mercuryIconFree;
    unsigned venusIconCaught, venusIconFree;
    unsigned marsIconCaught, marsIconFree;
    unsigned jupiterIconCaught, jupiterIconFree;
    unsigned saturnIconCaught, saturnIconFree;
    unsigned uranusIconCaught, uranusIconFree;
    unsigned neptuneIconCaught, neptuneIconFree;
    unsigned plutoIconCaught, plutoIconFree;

    preprocessTexture(mercuryIconCaught, "Resources/captured1.png");
    preprocessTexture(mercuryIconFree, "Resources/uncaptured1.png");
    preprocessTexture(venusIconCaught, "Resources/captured2.png");
    preprocessTexture(venusIconFree, "Resources/uncaptured2.png");
    preprocessTexture(marsIconCaught, "Resources/captured3.png");
    preprocessTexture(marsIconFree, "Resources/uncaptured3.png");
    preprocessTexture(jupiterIconCaught, "Resources/captured4.png");
    preprocessTexture(jupiterIconFree, "Resources/uncaptured4.png");
    preprocessTexture(saturnIconCaught, "Resources/captured5.png");
    preprocessTexture(saturnIconFree, "Resources/uncaptured5.png");
    preprocessTexture(uranusIconCaught, "Resources/captured6.png");
    preprocessTexture(uranusIconFree, "Resources/uncaptured6.png");
    preprocessTexture(neptuneIconCaught, "Resources/captured7.png");
    preprocessTexture(neptuneIconFree, "Resources/uncaptured7.png");
    preprocessTexture(plutoIconCaught, "Resources/captured8.png");
    preprocessTexture(plutoIconFree, "Resources/uncaptured8.png");

    unsigned skysphereTexture;
    preprocessHDRTexture(skysphereTexture,"Resources/starmap_2020_4k_gal.hdr");

    preprocessTexture(sunTexture, "Resources/2k_sun.jpg");
    preprocessTexture(mercuryTexture, "Resources/2k_mercury.jpg");
    preprocessTexture(venusTexture, "Resources/2k_venus_surface.jpg");
    preprocessTexture(earthTexture, "Resources/2k_earth_daymap.jpg");
    preprocessTexture(marsTexture, "Resources/2k_mars.jpg");
    preprocessTexture(jupiterTexture, "Resources/2k_jupiter.jpg");
    preprocessTexture(saturnTexture, "Resources/2k_saturn.jpg");
    preprocessTexture(uranusTexture, "Resources/2k_uranus.jpg");
    preprocessTexture(neptuneTexture, "Resources/2k_neptune.jpg");
    preprocessTexture(plutoTexture, "Resources/2k_ceres_fictional.jpg");
    preprocessTexture(saturnRingTexture, "Resources/2k_saturn_ring_alpha.png");

    //planet sky textures

    preprocessTexture(mercurySkyTexture, "Resources/mercury_sky.png");
    preprocessTexture(venusSkyTexture, "Resources/venus_sky.png");
    preprocessTexture(marsSkyTexture, "Resources/mars_sky.png");
    preprocessTexture(jupiterSkyTexture, "Resources/jupiter_sky.png");
    preprocessTexture(saturnSkyTexture, "Resources/saturn_sky.png");
    preprocessTexture(uranusSkyTexture, "Resources/uranus_sky.png");
    preprocessTexture(neptuneSkyTexture, "Resources/neptune_sky.png");
    preprocessTexture(plutoSkyTexture, "Resources/pluto_sky.png");
    preprocessHDRTexture(earthSkyTexture, "Resources/golden_gate_hills_4k.hdr");

    //elementi u raketi
    preprocessTexture(windowTexture, "Resources/Glass-Texture-Transparent.png");
    preprocessTexture(dashboardTexture, "Resources/dashboard.png");
    preprocessTexture(distanceCoverTexture, "Resources/distancecover.png");
    preprocessTexture(wasdTexture, "Resources/wasd.png");
    preprocessTexture(takeoffTexture, "Resources/takeoff-land.png");

    //hintovi
    preprocessTexture(nametagTexture, "Resources/nametag.png");
    preprocessTexture(goalTexture, "Resources/goal.png");
    preprocessTexture(onboardTexture, "Resources/take-onboard.png");
    preprocessTexture(missionAccomplishedTexture, "Resources/mission-accomplished.png");
    preprocessTexture(missionFailedTexture, "Resources/mission-failed.png");

    float scaleFactor = 1.0f;
    float distanceFactor = 1.0f;

    std::vector<Planet> planets = {
    { 0.0f*distanceFactor, 1.0f *scaleFactor, sunTexture },   // Sun
    { 2.0f*distanceFactor, 0.08f*scaleFactor, mercuryTexture },  // Mercury
    { 3.0f*distanceFactor, 0.12f * scaleFactor, venusTexture },  // Venus
    { 4.0f * distanceFactor, 0.13f * scaleFactor, earthTexture },  // Earth
    { 5.0f * distanceFactor, 0.10f * scaleFactor, marsTexture },  // Mars
    { 7.0f * distanceFactor, 0.40f * scaleFactor, jupiterTexture },  // Jupiter
    { 9.0f * distanceFactor, 0.35f * scaleFactor, saturnTexture },  // Saturn
    {11.0f * distanceFactor, 0.25f * scaleFactor, uranusTexture },  // Uranus
    {13.0f * distanceFactor, 0.24f * scaleFactor, neptuneTexture },  // Neptune
    {16.0f * distanceFactor, 0.05f * scaleFactor, plutoTexture }   // Pluto
    };

    // ---------------- VERTICES ----------------

    //Sun
    SphereMesh ballMesh = generateSphereTextured(1.0f, 40, 40);

    float* ballVertices = ballMesh.vertices.data();
    size_t ballSize = ballMesh.vertices.size() * sizeof(float);

    //Planets

    SphereMesh planetMesh=generatePlanetTextured(1.0f, 40, 40);
    float* planetVertices = planetMesh.vertices.data();
    size_t planetSize = planetMesh.vertices.size() * sizeof(float);


    // SKY SPHERE 
    SphereMesh skySphereMesh = generateSphereTextured(1.0f, 32, 16);

    //RING
    RingMesh saturnRing = generateRing(1.2f, 2.2f, 128);

    float* ringVertices = saturnRing.vertices.data();
    size_t ringSize = saturnRing.vertices.size() * sizeof(float);

    //Aliens
    AlienModel alien, alien1, alien2, alien3, alien4, alien5, alien6, alien7, alien8;
    alien1.load("Resources/aliens/alien1.glb");
    alien2.load("Resources/aliens/alien2.glb");
    alien3.load("Resources/aliens/alien3.glb");
    alien4.load("Resources/aliens/alien7.glb");
    alien5.load("Resources/aliens/alien5.glb");
    alien6.load("Resources/aliens/alien6.glb");
    alien7.load("Resources/aliens/alien9.glb");
    alien8.load("Resources/aliens/alien12.glb");

    //crosshair
    float aspect = (float)mode->width / (float)mode->height;
    std::vector<float> crosshairData = generateCrosshairVertices(aspect);

    //overlay video

    std::vector<unsigned int> videoFrames;

    // Učitava frejmove
    int totalFrames = 607; 
    videoFrames.reserve(totalFrames); 

    for (int i = 0; i < totalFrames; i++) {
        char path[128];
        sprintf_s(path, "Resources/Video/frame_%04d.png", i);

        unsigned int textureID;
        preprocessTexture(textureID, path);
        videoFrames.push_back(textureID);
    }


    // ---------------- SHADERS ----------------
    unsigned nametagShader, distanceBgShader, unifiedShader, skysphereShader, planetShader, alienShader, videoShader, glassShader;
    loadAllShaders(nametagShader, distanceBgShader, skysphereShader,unifiedShader, planetShader, alienShader, videoShader,glassShader);


    // ---------------- VAOs ----------------
    unsigned VAOnametag, VAOdistanceBg;
    unsigned VAOball;
    unsigned VAOplanet;
    unsigned VAOskySphere;
    unsigned VAOsaturnRing;
    unsigned VAOcrosshair;
    unsigned videoVAO;


    formVAOs(
        verticesNametag, sizeof(verticesNametag), VAOnametag,
        verticesTopLeftRect, sizeof(verticesTopLeftRect), VAOdistanceBg,
        skySphereMesh, VAOskySphere,
        ballMesh, VAOball,
        planetMesh, VAOplanet,
        saturnRing, VAOsaturnRing,
        crosshairData.data(), crosshairData.size() * sizeof(float), VAOcrosshair,
        videoVertices, videoVAO
    );
    // setup za video
    float frameTimer = 0.0f;
    int currentFrame = 0;
    float frameDuration = 1.0f / 24.0f; 



    // ---------------- MAIN LOOP ----------------
    double lastTime = glfwGetTime();
    const double targetFPS = 75.0;
    const double targetFrameTime = 1.0 / targetFPS; 

    while (!glfwWindowShouldClose(window)) {

  	  // Frame time calculation
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        //frame progress update za video
        frameTimer += deltaTime;
        if (frameTimer >= frameDuration) {
            currentFrame = (currentFrame + 1) % videoFrames.size();
            frameTimer = 0.0f;
        }

        //input
        processInput(window, deltaTime, distanceFactor, planets,state);

        /////////////////////////////////
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera matrices
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(fov),
            (float)mode->width / (float)mode->height,
            0.1f, 100.0f);

        // ---DRAW 3D---
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        switch (state) {

        case 0: {
            // Skysphere
            drawSkySphere(
                skysphereShader,
                VAOskySphere,
                skysphereTexture,
                skySphereMesh,
                projection,
                view
            );


            glm::mat4 ringModel = glm::mat4(1.0f);
            ringModel = glm::translate(ringModel, glm::vec3(9.0f, 0.0f, 0.0f));
            ringModel = glm::rotate(
                ringModel,
                glm::radians(20.0f),
                glm::vec3(0, 0, 1)
            );
            ringModel = glm::scale(ringModel, glm::vec3(0.35f));

            drawRing(
                unifiedShader,
                VAOsaturnRing,
                saturnRingTexture,
                saturnRing,
                ringModel,
                projection,
                view
            );

            // Planets

            for (int i = 0; i < planets.size(); i++) {
                const auto& p = planets[i];
                glm::mat4 model = glm::mat4(1.0f);

                model = glm::translate(model, glm::vec3(p.x, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
                model = glm::scale(model, glm::vec3(p.scale));
                if (i == 0) {
                    drawSphere(
                        unifiedShader,
                        VAOball,
                        p.texture,
                        ballMesh,
                        model,
                        projection,
                        view
                    );
                }
                else {
                drawPlanetWithLighting(
					planetShader,
					VAOplanet,
					p.texture,
					planetMesh,
					model,
					projection,
					view,
					glm::vec3(0.0f),
					cameraPos
				);
                }
            }
            break;
        }
        case 1: {

            drawSkySphere(skysphereShader, VAOskySphere, mercurySkyTexture, skySphereMesh, projection, view);
            if (!mercuryCaught) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3(0.4f));
                drawAlien(alienShader, alien1, model, projection, view, cameraPos);
            }
            break;
        }
        case 2: {
            drawSkySphere(
                skysphereShader,
                VAOskySphere,
                venusSkyTexture,
                skySphereMesh,
                projection,
                view
            );
            if (!venusCaught) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3(0.4f));

                drawAlien(
                    alienShader,
                    alien2,
                    model,
                    projection,
                    view, cameraPos
                );
            }
            break;
        }
        case 3: {

            if (mercuryCaught && venusCaught && marsCaught && jupiterCaught && saturnCaught && uranusCaught && neptuneCaught && plutoCaught) {
                drawSkySphere(
                    skysphereShader,
                    VAOskySphere,
                    earthSkyTexture,
                    skySphereMesh,
                    projection,
                    view
                );

                std::vector<AlienModel*> aliens = {
                    &alien1, &alien2, &alien3, &alien4,
                    &alien5, &alien6, &alien7, &alien8
                };

                glm::vec3 earthPos = glm::vec3(planets[3].x, 0.0f, 0.0f);

                int count = aliens.size();
                float radius = 10.0f;
                float arcAngle = glm::radians(120.0f);
                float startAngle = -arcAngle / 2.0f;

                for (int i = 0; i < count; i++) {
                    float t = (count == 1) ? 0.0f : (float)i / (count - 1);
                    float angle = startAngle + t * arcAngle;

                    float x = sin(angle) * 8.0f;
                    float z = cos(angle) * radius;

                    glm::vec3 alienPos = earthPos + glm::vec3(x, 0.0f, z);

                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
                    model = glm::scale(model, glm::vec3(0.5f));

                    if (i == 1) {
                        model = glm::rotate(
                            model,
                            glm::radians(180.0f),
                            glm::vec3(0.0f, 0.0f, 1.0f)
                        );
                    }
                    if (i == 3) {
                        model = glm::scale(model, glm::vec3(3.0f));
                    }

                    drawAlienStationary(
                        alienShader,
                        *aliens[i],
                        model,
                        projection,
                        view,
                        cameraPos,
                        alienPos
                    );
                }
                glUseProgram(nametagShader);
                glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);
                glBindTexture(GL_TEXTURE_2D, missionAccomplishedTexture);
                glBindVertexArray(videoVAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
            else {
                glUseProgram(nametagShader);
                glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);
                glBindTexture(GL_TEXTURE_2D, missionFailedTexture);
                glBindVertexArray(videoVAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
            break;
        }

        case 4: {
            drawSkySphere(
                skysphereShader,
                VAOskySphere,
                marsSkyTexture,
                skySphereMesh,
                projection,
                view
            );
            //set alien model
            if (!marsCaught) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3(0.8f));

                drawAlien(
                    alienShader,
                    alien3,
                    model,
                    projection,
                    view, cameraPos
                );
            }
            break;
        }
        case 5: {
            drawSkySphere(
                skysphereShader,
                VAOskySphere,
                jupiterSkyTexture,
                skySphereMesh,
                projection,
                view
            );
            //set alien model
            if (!jupiterCaught) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3(1.2f));

                drawAlien(
                    alienShader,
                    alien4,
                    model,
                    projection,
                    view, cameraPos
                );
            }
            break;
        }
        case 6: {
            drawSkySphere(
                skysphereShader,
                VAOskySphere,
                saturnSkyTexture,
                skySphereMesh,
                projection,
                view
            );
            //set alien model
            if (!saturnCaught) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3(0.4f));

                drawAlien(
                    alienShader,
                    alien5,
                    model,
                    projection,
                    view, cameraPos
                );
            }
            break;
        }
        case 7: {
            drawSkySphere(
                skysphereShader,
                VAOskySphere,
                uranusSkyTexture,
                skySphereMesh,
                projection,
                view
            );
            //set alien model
            if (!uranusCaught) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3(0.4f));

                drawAlien(
                    alienShader,
                    alien6,
                    model,
                    projection,
                    view, cameraPos
                );
            }
            break;
        }
        case 8: {
            drawSkySphere(
                skysphereShader,
                VAOskySphere,
                neptuneSkyTexture,
                skySphereMesh,
                projection,
                view
            );
            //set alien model
            if (!neptuneCaught) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3(0.4f));

                drawAlien(
                    alienShader,
                    alien7,
                    model,
                    projection,
                    view, cameraPos
                );
            }
            break;
        }
        case 9: {
            drawSkySphere(
                skysphereShader,
                VAOskySphere,
                plutoSkyTexture,
                skySphereMesh,
                projection,
                view
            );
            //set alien model
            if (!plutoCaught) {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
                model = glm::scale(model, glm::vec3(0.4f));

                drawAlien(
                    alienShader,
                    alien8,
                    model,
                    projection,
                    view, cameraPos
                );
            }
            break;
        }

        }

         // ---DRAW 2D---
        glDepthMask(GL_FALSE); 

        //video overlay

        if (state == 0) {

            //staklo
            glUseProgram(glassShader);
            glUniform1i(glGetUniformLocation(glassShader, "glassTexture"), 0);
            glBindTexture(GL_TEXTURE_2D, windowTexture);
            glBindVertexArray(videoVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //raketa video
            glUseProgram(videoShader);
            glUniform1i(glGetUniformLocation(videoShader, "videoTexture"), 0);
            glBindTexture(GL_TEXTURE_2D, videoFrames[currentFrame]);
            glBindVertexArray(videoVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);


            //crew dashboard
            glUseProgram(nametagShader);
            glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);
            glBindTexture(GL_TEXTURE_2D, dashboardTexture);
            glBindVertexArray(videoVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //alien icons:


            drawAlienIcon(nametagShader, videoVAO, mercuryCaught ? mercuryIconCaught : mercuryIconFree);
            drawAlienIcon(nametagShader, videoVAO, venusCaught ? venusIconCaught : venusIconFree);
            drawAlienIcon(nametagShader, videoVAO, marsCaught ? marsIconCaught : marsIconFree);
            drawAlienIcon(nametagShader, videoVAO, jupiterCaught ? jupiterIconCaught : jupiterIconFree);
            drawAlienIcon(nametagShader, videoVAO, saturnCaught ? saturnIconCaught : saturnIconFree);
            drawAlienIcon(nametagShader, videoVAO, uranusCaught ? uranusIconCaught : uranusIconFree);
            drawAlienIcon(nametagShader, videoVAO, neptuneCaught ? neptuneIconCaught : neptuneIconFree);
            drawAlienIcon(nametagShader, videoVAO, plutoCaught ? plutoIconCaught : plutoIconFree);

            glUseProgram(nametagShader);
            glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);
            glBindTexture(GL_TEXTURE_2D, distanceCoverTexture);
            glBindVertexArray(videoVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            //distanca pređena

            float realSunEarthKm = 150.0e6f;
            float simDistanceSunEarth = (planets[3].x - planets[0].x) * distanceFactor;
            float simUnitToKm = realSunEarthKm / simDistanceSunEarth;
            float distanceInBillionsKm = simDistanceTravelled * simUnitToKm / 1e9f;


            char buffer[64];
            sprintf_s(buffer, "%.2f billions of km", distanceInBillionsKm);

            float textScale = 0.7f;
            float xPos = (mode->width / 2.0f) - 48.0f;
            float yPos = 322.0f;

            textRenderer.RenderText(buffer, xPos, yPos, textScale, glm::vec3(1.0f, 1.0f, 1.0f));

            //WASD dashboard
            if (!isNearPlanet) {
                glUseProgram(nametagShader);
                glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);
                glBindTexture(GL_TEXTURE_2D, wasdTexture);
                glBindVertexArray(videoVAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
            else {
                glUseProgram(nametagShader);
                glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);
                glBindTexture(GL_TEXTURE_2D, takeoffTexture);
                glBindVertexArray(videoVAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            
            }
        

            if (!hasMovedAtAll) {
                glUseProgram(nametagShader);
                glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);
                glBindTexture(GL_TEXTURE_2D, goalTexture);
                glBindVertexArray(videoVAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            
            }

            //nametag

            glUseProgram(nametagShader);
            glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);
            glBindTexture(GL_TEXTURE_2D, nametagTexture);
            glBindVertexArray(videoVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);


        }

        

        //kursor

        if (state != 0) {
            glUseProgram(distanceBgShader);
            glUniform3f(glGetUniformLocation(distanceBgShader, "uColor"), 1.0f, 1.0f, 1.0f);
            glBindVertexArray(VAOcrosshair);
            glDrawArrays(GL_TRIANGLES, 0, 12);

            //ako nismo nikad uhvatili vanzemaljca, imamo hint

            if (!mercuryCaught && !venusCaught && !marsCaught && !jupiterCaught && !saturnCaught && !uranusCaught && !neptuneCaught && !plutoCaught) {
                glUseProgram(nametagShader);
                glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);
                glBindTexture(GL_TEXTURE_2D, onboardTexture);
                glBindVertexArray(videoVAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }

        }

        glDepthMask(GL_TRUE); 

        glfwSwapBuffers(window);
        glfwPollEvents();

        // FRAME LIMITER 
        double frameEnd = glfwGetTime();
        double frameDuration = frameEnd - currentTime;

        if (frameDuration < targetFrameTime) {
            double sleepTime = (targetFrameTime - frameDuration) * 1000.0;

            std::this_thread::sleep_for(std::chrono::milliseconds((int)sleepTime));
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
