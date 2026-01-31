#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec4 vColor; // Input from vertex shader

uniform sampler2D alienTexture;
uniform bool hasTexture; // Useful toggle

void main() {
    vec4 texColor = texture(alienTexture, TexCoord);
   
    FragColor = vColor; 
}
