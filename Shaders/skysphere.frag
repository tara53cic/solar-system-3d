#version 330 core
out vec4 FragColor;

in vec3 WorldPos;
uniform sampler2D skyTexture;

const vec2 invAtan = vec2(0.1591, 0.3183);

vec2 sampleSphericalMap(vec3 v)
{
    vec2 uv = vec2(atan(v.z, v.x), asin(v.y));
    uv *= invAtan;
    uv += 0.5;
    return uv;
}

void main()
{
    vec3 dir = normalize(WorldPos);
    vec2 uv = sampleSphericalMap(dir);

    vec3 color = texture(skyTexture, uv).rgb;

    // Optional subtle darkening
    color *= 0.95;

    FragColor = vec4(color, 1.0);
}
