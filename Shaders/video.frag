#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D videoTexture;

void main() {
    vec4 texColor = texture(videoTexture, TexCoords);
    
    vec3 keyColor = vec3(0.0, 0.682, 0.243); 
    

    float dist = distance(texColor.rgb, keyColor);
    
    float similarity = 0.25;  
    float edgeSoftness = 0.05; 
    
    float alpha = smoothstep(similarity, similarity + edgeSoftness, dist);
    
    if (alpha < 0.01) discard; 

    FragColor = vec4(texColor.rgb, alpha);
}