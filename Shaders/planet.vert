#version 330 core
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal; 
layout(location = 2) in vec4 inCol;
layout(location = 3) in vec2 inUV;

uniform mat4 uM;
uniform mat4 uV;
uniform mat4 uP;

out vec2 fragUV;
out vec3 fragNormal;
out vec3 fragPos; 

void main() {
    fragPos = vec3(uM * vec4(inPos, 1.0));

    fragNormal = mat3(transpose(inverse(uM))) * inNormal;
    fragUV = inUV;
    gl_Position = uP * uV * vec4(fragPos, 1.0);
}