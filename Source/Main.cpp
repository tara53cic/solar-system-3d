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

unsigned windowTexture, dashboardTexture, distanceCoverTexture;


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

    glEnable(GL_DEPTH_TEST); // bitno za 3D scene

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
    unsigned nametagTexture, distanceBgTexture;
    unsigned mercuryIconCaught, mercuryIconFree;
    unsigned venusIconCaught, venusIconFree;
    unsigned marsIconCaught, marsIconFree;
    unsigned jupiterIconCaught, jupiterIconFree;
    unsigned saturnIconCaught, saturnIconFree;
    unsigned uranusIconCaught, uranusIconFree;
    unsigned neptuneIconCaught, neptuneIconFree;
    unsigned plutoIconCaught, plutoIconFree;

    preprocessTexture(nametagTexture, "Resources/purpletransparent50.png");
    preprocessTexture(distanceBgTexture, "Resources/purpletransparent50.png");

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

    preprocessTexture(windowTexture, "Resources/Glass-Texture-Transparent.png");
    preprocessTexture(dashboardTexture, "Resources/dashboard.png");
    preprocessTexture(distanceCoverTexture, "Resources/distancecover.png");

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


    // SKY SPHERE (indexed, textured sphere)
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

    // Load the frames
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
    float frameDuration = 1.0f / 24.0f; // 24 FPS



    // ---------------- MAIN LOOP ----------------
    double lastTime = glfwGetTime();
    const double targetFPS = 75.0;
    const double targetFrameTime = 1.0 / targetFPS; // 0.013333 seconds

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
            drawSkySphere(
                skysphereShader,
                VAOskySphere,
                mercurySkyTexture,
                skySphereMesh,
                projection,
                view
            );
            //set alien model

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cameraPos + glm::vec3(0.0f, -0.5f, -2.5f));
            model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(-35.0f), glm::vec3(0.0f, 0.0f, 1.0f));

            model = glm::scale(model, glm::vec3(0.4f));

            drawAlien(
                alienShader,
                alien3,
                model,
                projection,
                view, cameraPos
            );
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
            float xPos = (mode->width / 2.0f) - 53.0f;
            float yPos = 322.0f;

            textRenderer.RenderText(buffer, xPos, yPos, textScale, glm::vec3(1.0f, 1.0f, 1.0f));


        }

        drawNametag(nametagShader, VAOnametag, nametagTexture);
        textRenderer.RenderText("Tara Petricic, RA 141/2022", 25.0f, 28.0f, 1.0f, glm::vec3(1.0f));

        

        //kursor

        if (state != 0) {
            glUseProgram(distanceBgShader);
            glUniform3f(glGetUniformLocation(distanceBgShader, "uColor"), 1.0f, 1.0f, 1.0f);
            glBindVertexArray(VAOcrosshair);
            glDrawArrays(GL_TRIANGLES, 0, 12);
        }

        glDepthMask(GL_TRUE); 

        glfwSwapBuffers(window);
        glfwPollEvents();

        // 4. FRAME LIMITER LOGIC
        double frameEnd = glfwGetTime();
        double frameDuration = frameEnd - currentTime;

        if (frameDuration < targetFrameTime) {
            // Calculate how long we need to wait in milliseconds
            double sleepTime = (targetFrameTime - frameDuration) * 1000.0;

            // Use high_resolution_clock for precise sleeping
            std::this_thread::sleep_for(std::chrono::milliseconds((int)sleepTime));
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
