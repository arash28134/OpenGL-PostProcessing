#version 330 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

uniform vec2 screenResolution;

void main()
{
    //sample our texture
	vec4 texColor = texture(screenTexture, texCoords);
	
	//determine origin
	vec2 position = (gl_FragCoord.xy / screenResolution.xy) - vec2(0.5);
		
	//determine the vector length of the center position
	float len = length(position);
	
	//show our vignette
	fragColor = vec4( texColor.rgb * (1.0 - len), 1.0);
}