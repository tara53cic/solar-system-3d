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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, alienIconTexture);

    glBindVertexArray(VAOalienIcon);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
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

    // 1. Define the Speed and Angle
    float orbitSpeed = 0.8f;
    float angle = time * orbitSpeed; // This angle is shared by both movements
    float radius = 8.0f;

    // 2. Orbit Math (relative to camera)
    float orbitX = cos(angle) * radius;
    float orbitZ = sin(angle) * radius;
    float bobbing = sin(time * 2.0f) * 0.5f;

    // 3. Build the World Matrix
    // Start with identity
    glm::mat4 animatedModel = glm::mat4(1.0f);

    // A. Move to the orbit position relative to the camera
    animatedModel = glm::translate(animatedModel, cameraPos + glm::vec3(orbitX, bobbing, orbitZ));

    // B. Self-Rotation (Synced to the orbit)
    // We use the same 'angle' variable. 
    // Note: You might need to adjust the axis (0,0,1) or (0,1,0) depending on 
    // your GLB's original orientation, but usually it's Y-up (0,1,0).
    // Because you tilted the alien -90 on X in 'model', we rotate it HERE first.
    animatedModel = glm::rotate(animatedModel, -angle, glm::vec3(0.0f, 1.0f, 0.0f));

    // C. Apply the Base Pose (Scale and Tilt from main)
    animatedModel = animatedModel * model;

    // 4. Send to Shader
    glUniformMatrix4fv(glGetUniformLocation(alienShader, "model"), 1, GL_FALSE, glm::value_ptr(animatedModel));
    glUniformMatrix4fv(glGetUniformLocation(alienShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(alienShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glUniform1i(glGetUniformLocation(alienShader, "alienTexture"), 0);
    alien.draw();
}

