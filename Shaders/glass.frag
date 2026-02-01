#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D glassTexture;
uniform vec3 lightDir = vec3(0.5, 0.5, 1.0);

void main() {
    vec4 texColor = texture(glassTexture, TexCoords);
    
    float baseAlpha = 0.2;
    

    float luminance = dot(texColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    float tintEffect = luminance * 0.3; 
    
    float spec = pow(max(dot(vec3(0.0, 0.0, 1.0), normalize(lightDir)), 0.0), 32.0);
    vec3 glint = vec3(1.0) * spec * 0.5;

    vec3 finalColor = texColor.rgb * 0.1 + glint;
    float finalAlpha = baseAlpha + tintEffect;

    FragColor = vec4(finalColor, finalAlpha);
}