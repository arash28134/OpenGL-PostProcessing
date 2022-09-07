#version 330 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

uniform vec2 screenResolution;

void main()
{
    // waving effect
    vec2 wavecoord = texCoords;
    wavecoord.x += sin(wavecoord.y * 4*2*3.14159 + 100) / 100;

    fragColor = texture(screenTexture, wavecoord);
}