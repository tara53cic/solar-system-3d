#include "../Header/Shaders.h"
#include "../Header/Util.h"
#include <GL/glew.h>

unsigned int loadAllShaders(
    unsigned int& nametagShader,
    unsigned int& distanceBackgroundShader,
    unsigned int& skySphereShader,
    unsigned int& sphereShader,
    unsigned int& planetShader,
    unsigned int& alienShader,
    unsigned int& videoShader,
    unsigned int& glassShader)
{


    nametagShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    glUseProgram(nametagShader);
    glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);

    distanceBackgroundShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    glUseProgram(distanceBackgroundShader);
    glUniform1i(glGetUniformLocation(distanceBackgroundShader, "uTex0"), 0);


    sphereShader = createShader("Shaders/3dshader.vert", "Shaders/3dshader.frag");

    planetShader= createShader("Shaders/planet.vert", "Shaders/planet.frag");

    skySphereShader = createShader(
        "Shaders/skysphere.vert",
        "Shaders/skysphere.frag"
    );

    alienShader = createShader("Shaders/alien.vert", "Shaders/alien.frag");

    videoShader = createShader("Shaders/video.vert", "Shaders/video.frag");

    glassShader = createShader("Shaders/glass.vert", "Shaders/glass.frag");


    return 1;
}