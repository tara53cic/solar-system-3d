#include "../Header/AlienModel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GL/glew.h> 
#include "../Header/stb_image.h"

#include <iostream>

struct ModelVertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;
    glm::vec4 color; 
};

GLuint AlienModel::loadTextureFromFile(const std::string& path) {
    int w, h, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << path << "\n";
        return 0;
    }

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return texID;
}

GLuint AlienModel::loadTextureFromAssimp(const aiScene* scene, aiMaterial* mat, const std::string& modelDir) {
    aiString texPath;
    if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &texPath) != AI_SUCCESS)
        return 0;

    GLuint texID = 0;
    if (texPath.C_Str()[0] == '*') {
        int texIndex = std::stoi(texPath.C_Str() + 1);
        const aiTexture* tex = scene->mTextures[texIndex];

        int w, h, channels;
        unsigned char* data = nullptr;

        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        if (tex->mHeight == 0) {
            data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(tex->pcData),
                tex->mWidth, &w, &h, &channels, 4);
            if (!data) return 0;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->mWidth, tex->mHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, tex->pcData);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::string fullPath = modelDir + texPath.C_Str();
        texID = loadTextureFromFile(fullPath);
    }

    return texID;
}

bool AlienModel::load(const std::string& path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_FlipUVs 
    );

    if (!scene || !scene->HasMeshes()) {
        std::cerr << "Assimp error: " << importer.GetErrorString() << "\n";
        return false;
    }

    meshes.clear();
    std::string modelDir = path.substr(0, path.find_last_of("/\\") + 1);

    for (unsigned int mIdx = 0; mIdx < scene->mNumMeshes; ++mIdx) {
        aiMesh* m = scene->mMeshes[mIdx];

        std::vector<ModelVertex> vertices;
        std::vector<unsigned int> indices;

        for (unsigned int i = 0; i < m->mNumVertices; ++i) {
            ModelVertex v;
            v.pos = { m->mVertices[i].x, m->mVertices[i].y, m->mVertices[i].z };
            v.normal = { m->mNormals[i].x, m->mNormals[i].y, m->mNormals[i].z };

            v.uv = (m->mTextureCoords[0]) ? glm::vec2(m->mTextureCoords[0][i].x, m->mTextureCoords[0][i].y)
                : glm::vec2(0.0f, 0.0f);

            if (m->HasVertexColors(0)) {
                v.color = glm::vec4(m->mColors[0][i].r, m->mColors[0][i].g, m->mColors[0][i].b, m->mColors[0][i].a);
            }
            else {
                v.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            }

            vertices.push_back(v);
        }

        for (unsigned int f = 0; f < m->mNumFaces; ++f) {
            aiFace face = m->mFaces[f];
            for (unsigned int j = 0; j < face.mNumIndices; ++j)
                indices.push_back(face.mIndices[j]);
        }

        Mesh mesh{};
        mesh.indexCount = indices.size();

        glGenVertexArrays(1, &mesh.VAO);
        glGenBuffers(1, &mesh.VBO);
        glGenBuffers(1, &mesh.EBO);

        glBindVertexArray(mesh.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(ModelVertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Location 0: Pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)0);
        glEnableVertexAttribArray(0);

        // Location 1: Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, normal));
        glEnableVertexAttribArray(1);

        // Location 2: UV
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, uv));
        glEnableVertexAttribArray(2);

        // Location 3: Color
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, color));
        glEnableVertexAttribArray(3);

        glBindVertexArray(0);

        mesh.texture = 0;
        if (scene->HasMaterials()) {
            aiMaterial* mat = scene->mMaterials[m->mMaterialIndex];
            mesh.texture = loadTextureFromAssimp(scene, mat, modelDir);
        }

        meshes.push_back(mesh);
    }

    return true;
}

void AlienModel::draw() const {
    for (const auto& mesh : meshes) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh.texture);
        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, 0);
    }
    glBindVertexArray(0);
}