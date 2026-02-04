#version 330 core
in vec2 fragUV;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 outColor;

uniform sampler2D uTexture;
uniform vec3 uSunPos;   
uniform vec3 uViewPos;  

void main() {
    vec3 texColor = texture(uTexture, fragUV).rgb;
    
    vec3 ambient = 0.1 * texColor;

    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(uSunPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * texColor;

    outColor = vec4(ambient + diffuse, 1.0);
}