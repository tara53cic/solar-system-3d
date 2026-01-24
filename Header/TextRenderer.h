#pragma once
#include <map>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "Util.h"

struct Character {
    GLuint TextureID;   // ID of glyph texture
    glm::ivec2 Size;    // width and height of glyph
    glm::ivec2 Bearing; // offset from baseline to left/top of glyph
    GLuint Advance;     // horizontal offset to advance to next glyph
};

class TextRenderer {
public:
    std::map<char, Character> Characters;
    GLuint VAO, VBO;
    GLuint shader;

    TextRenderer(unsigned int width, unsigned int height);
    void Load(std::string fontPath, unsigned int fontSize);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
    float GetTextWidth(const std::string& text, float scale);
};

