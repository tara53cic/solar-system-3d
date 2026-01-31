#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/scene.h>

class AlienModel {
public:
    struct Mesh {
        GLuint VAO = 0;
        GLuint VBO = 0;
        GLuint EBO = 0;
        GLuint texture = 0;
        unsigned int indexCount = 0;
    };

    std::vector<Mesh> meshes;

    bool load(const std::string& path);
    void draw() const;

private:
    GLuint loadTextureFromFile(const std::string& path);
    GLuint loadTextureFromAssimp(const aiScene* scene, aiMaterial* mat, const std::string& modelDir);
};

#pragma once
