#include "../Header/Draw.h"         

void drawBackground(unsigned int backgroundShader, unsigned int VAOrect, unsigned int backgroundTexture) {

    glUseProgram(backgroundShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glBindVertexArray(VAOrect);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawNametag(unsigned int nametagShader, unsigned int VAOnametag, unsigned int nametagTexture) {

    glUseProgram(nametagShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, nametagTexture);

    glBindVertexArray(VAOnametag);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawDistanceBackground(unsigned int distanceBackgroundShader, unsigned int VAOdistanceBackground, unsigned int distanceBackgroundTexture) {

    glUseProgram(distanceBackgroundShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, distanceBackgroundTexture);

    glBindVertexArray(VAOdistanceBackground);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawAlienIcon(unsigned int alienIconShader, unsigned int VAOalienIcon, unsigned int alienIconTexture) {

    glUseProgram(alienIconShader);
    glUniform1i(glGetUniformLocation(alienIconShader, "uTex0"), 0);
    glBindTexture(GL_TEXTURE_2D, alienIconTexture);
    glBindVertexArray(VAOalienIcon);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawHelp(unsigned int backgroundShader, unsigned int VAOrect, unsigned int backgroundTexture) {

    glUseProgram(backgroundShader);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glBindVertexArray(VAOrect);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

void drawSkySphere(
    unsigned int skysphereShader,
    unsigned int VAOskySphere,
    unsigned int skysphereTexture,
    const SphereMesh& skySphereMesh,
    glm::mat4 projection,
    glm::mat4 view
) {

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    glUseProgram(skysphereShader);

    glm::mat4 skyView = glm::mat4(glm::mat3(view));
    glUniformMatrix4fv(glGetUniformLocation(skysphereShader, "view"), 1, GL_FALSE, glm::value_ptr(skyView));
    glUniformMatrix4fv(glGetUniformLocation(skysphereShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, skysphereTexture);

    glBindVertexArray(VAOskySphere);
    glDrawElements(
        GL_TRIANGLES,
        skySphereMesh.indices.size(),
        GL_UNSIGNED_INT,
        0
    );


    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

}

void drawSphere(
    unsigned int unifiedShader,
    unsigned int VAOball,
    unsigned int planetTexture,
    const SphereMesh& ballMesh,
    const glm::mat4& model,
    const glm::mat4& projection,
    const glm::mat4& view
) {
    glUseProgram(unifiedShader);

    glUniformMatrix4fv(
        glGetUniformLocation(unifiedShader, "uV"),
        1, GL_FALSE, glm::value_ptr(view)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(unifiedShader, "uP"),
        1, GL_FALSE, glm::value_ptr(projection)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(unifiedShader, "uM"),
        1, GL_FALSE, glm::value_ptr(model)
    );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, planetTexture);
    glUniform1i(glGetUniformLocation(unifiedShader, "uTexture"), 0);

    glBindVertexArray(VAOball);
    glDrawElements(GL_TRIANGLES, ballMesh.indices.size(), GL_UNSIGNED_INT, 0);
}

void drawPlanetWithLighting(
    unsigned int planetShader,
    unsigned int VAOball,
    unsigned int planetTexture,
    const SphereMesh& ballMesh,
    const glm::mat4& model,
    const glm::mat4& projection,
    const glm::mat4& view,
    const glm::vec3& sunPos,
    const glm::vec3& cameraPos
) {
    glUseProgram(planetShader);
    glUniformMatrix4fv(glGetUniformLocation(planetShader, "uV"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(planetShader, "uP"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(planetShader, "uM"), 1, GL_FALSE, glm::value_ptr(model));

    // Light uniforms
    glUniform3fv(glGetUniformLocation(planetShader, "uSunPos"), 1, glm::value_ptr(sunPos));
    glUniform3fv(glGetUniformLocation(planetShader, "uViewPos"), 1, glm::value_ptr(cameraPos));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, planetTexture);
    glUniform1i(glGetUniformLocation(planetShader, "uTexture"), 0);

    glBindVertexArray(VAOball);
    glDrawElements(GL_TRIANGLES, ballMesh.indices.size(), GL_UNSIGNED_INT, 0);
}

void drawRing(
    unsigned int unifiedShader,
    unsigned int VAOring,
    unsigned int ringTexture,
    const RingMesh& ringMesh,
    const glm::mat4& model,
    const glm::mat4& projection,
    const glm::mat4& view
) {
    glUseProgram(unifiedShader);

    glUniformMatrix4fv(
        glGetUniformLocation(unifiedShader, "uV"),
        1, GL_FALSE, glm::value_ptr(view)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(unifiedShader, "uP"),
        1, GL_FALSE, glm::value_ptr(projection)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(unifiedShader, "uM"),
        1, GL_FALSE, glm::value_ptr(model)
    );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ringTexture);
    glUniform1i(glGetUniformLocation(unifiedShader, "uTexture"), 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    glBindVertexArray(VAOring);
    glDrawElements(GL_TRIANGLES, ringMesh.indices.size(), GL_UNSIGNED_INT, 0);



}

void drawAlien(unsigned int alienShader, AlienModel& alien, const glm::mat4& model,
    const glm::mat4& projection, const glm::mat4& view, glm::vec3 cameraPos) {

    glUseProgram(alienShader);
    float time = (float)glfwGetTime();

    // animacija...
    float orbitSpeed = 0.5f;
    float angle = time * orbitSpeed; 
    float radius = 8.0f;


    float orbitX = cos(angle) * radius;
    float orbitZ = sin(angle) * radius;
    float bobbing = sin(time * 2.0f) * 0.5f;


    glm::mat4 animatedModel = glm::mat4(1.0f);

    animatedModel = glm::translate(animatedModel, cameraPos + glm::vec3(orbitX, bobbing, orbitZ));
    animatedModel = glm::rotate(animatedModel, -angle, glm::vec3(0.0f, 1.0f, 0.0f));

    // originalni model transf
    animatedModel = animatedModel * model;

    glUniformMatrix4fv(glGetUniformLocation(alienShader, "model"), 1, GL_FALSE, glm::value_ptr(animatedModel));
    glUniformMatrix4fv(glGetUniformLocation(alienShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(alienShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform1i(glGetUniformLocation(alienShader, "alienTexture"), 0);
    alien.draw();
}

