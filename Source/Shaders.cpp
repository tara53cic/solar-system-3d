#include "../Header/Shaders.h"
#include "../Header/Util.h"
#include <GL/glew.h>

unsigned int loadAllShaders(
    unsigned int& nametagShader,
    unsigned int& distanceBackgroundShader,
    unsigned int& alienIconShader,
    unsigned int& skySphereShader,
    unsigned int& sphereShader,
    unsigned int& alienShader)
{


    nametagShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    glUseProgram(nametagShader);
    glUniform1i(glGetUniformLocation(nametagShader, "uTex0"), 0);

    distanceBackgroundShader = createShader("Shaders/rect.vert", "Shaders/rect.frag");
    glUseProgram(distanceBackgroundShader);
    glUniform1i(glGetUniformLocation(distanceBackgroundShader, "uTex0"), 0);

    alienIconShader= createShader("Shaders/rect.vert", "Shaders/rect.frag");
    glUseProgram(alienIconShader);
    glUniform1i(glGetUniformLocation(alienIconShader, "uTex0"), 0);

    sphereShader = createShader("Shaders/3dshader.vert", "Shaders/3dshader.frag");

    skySphereShader = createShader(
        "Shaders/skysphere.vert",
        "Shaders/skysphere.frag"
    );

    alienShader = createShader("Shaders/alien.vert", "Shaders/alien.frag");


    return 1;
}