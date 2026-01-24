#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 WorldPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    WorldPos = aPos;
    mat4 viewNoTranslate = mat4(mat3(view));
    gl_Position = projection * viewNoTranslate * vec4(aPos, 1.0);
}