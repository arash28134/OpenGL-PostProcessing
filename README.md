# OpenGL PostProcessing
OpenGL PostProcessing is a library written in C++ for OpenGL. it focuses on giving users a quick way to implement Post Processing in thier OpenGL project. it also has several Post Processing example shaders.

At the moment, library uses GLEW for better portability but you can easily modify it to use GLAD.
## Usage
You can use the library in just 5 steps!
- Include the header file:
```cpp
#include "postprocessing.h"
```
- Create a PostProcessing object:
```cpp
PostProcessing postProcessing;
```
- Initialize PostProcessing by calling `Initialize()` function. the first and second parameters are width and height of your window (Framebuffer that's going to get created) and third and fourth parameters are your vertex and fragment shader names (which will get compiled by library):
```cpp
postProcessing.Initialize(800, 600, "postprocessing.vs", "postprocessing.fs");
```
- At the start of your render loop, call the `StartProcessing()` function:
```cpp
// Loop until windows closed
while (!glfwWindowShouldClose(mainWindow))
{
	postProcessing.StartProcessing();
    ...
```
- At the end of your render loop right before `glfwSwapBuffers(mainWindow)`, call the `EndProcessing()` function:
```cpp
while (!glfwWindowShouldClose(mainWindow))
{
	postProcessing.StartProcessing();
    ...

    postProcessing.EndProcessing();

	// swap main window's buffers
	glfwSwapBuffers(mainWindow);
}
```
## Example effects
Raw (no effect applied)
```glsl
#version 330 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

uniform vec2 screenResolution;

void main()
{
    fragColor = texture(screenTexture, texCoords);
}
```
![Raw](screenshots/raw_noeffect.png?raw=true "Raw with no effects")

Inverse effect
```glsl
#version 330 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

uniform vec2 screenResolution;

void main()
{
    fragColor = vec4(1.0f) - texture(screenTexture, texCoords);
}
```
![Raw](screenshots/inverse_effect.png?raw=true "Raw with no effects")

Kernel effect
```glsl
#version 330 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

uniform vec2 screenResolution;

const float offset_x = 1.0f / 800.0f;  
const float offset_y = 1.0f / 800.0f;  

vec2 offsets[9] = vec2[]
(
    vec2(-offset_x,  offset_y), vec2( 0.0f,    offset_y), vec2( offset_x,  offset_y),
    vec2(-offset_x,  0.0f),     vec2( 0.0f,    0.0f),     vec2( offset_x,  0.0f),
    vec2(-offset_x, -offset_y), vec2( 0.0f,   -offset_y), vec2( offset_x, -offset_y) 
);

float kernel[9] = float[]
(
    1,  1, 1,
    1, -10, 1,
    1,  1, 1
);

void main()
{
    vec3 color = vec3(0.0f);
    for(int i = 0; i < 9; i++)
        color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * kernel[i];

    fragColor = vec4(color, 1.0f);
}
```
![Raw](screenshots/kernel_effect.png?raw=true "Raw with no effects")

Wave effect
```glsl
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
```
![Raw](screenshots/wave_effect.png?raw=true "Raw with no effects")

Kernel and Wave effects combined
```glsl
#version 330 core

out vec4 fragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

uniform vec2 screenResolution;

const float offset_x = 1.0f / 800.0f;  
const float offset_y = 1.0f / 800.0f;  

vec2 offsets[9] = vec2[]
(
    vec2(-offset_x,  offset_y), vec2( 0.0f,    offset_y), vec2( offset_x,  offset_y),
    vec2(-offset_x,  0.0f),     vec2( 0.0f,    0.0f),     vec2( offset_x,  0.0f),
    vec2(-offset_x, -offset_y), vec2( 0.0f,   -offset_y), vec2( offset_x, -offset_y) 
);

float kernel[9] = float[]
(
    1,  1, 1,
    1, -7, 1,
    1,  1, 1
);

void main()
{
    // kernel effect
    vec3 color = vec3(0.0f);
    for(int i = 0; i < 9; i++)
        color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * kernel[i];

    // waving effect
    vec2 texcoord = texCoords;
    texcoord.x += sin(texcoord.y * 4*2*3.14159 + 100) / 100;

    vec4 finalTexture = texture(screenTexture, texcoord);

    finalTexture /= vec4(color, 1.0f);

    fragColor = finalTexture;
}
```
![Raw](screenshots/kernel_and_wave_effect.png?raw=true "Raw with no effects")

Vignette effect
```glsl
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
```
![Raw](screenshots/vignette_effect.png?raw=true "Raw with no effects")
## Credits
Special thanks to [Victor Gordan](https://www.youtube.com/c/VictorGordan) for his video on [Framebuffer & PostProcessing](https://www.youtube.com/watch?v=QQ3jr-9Rc1o).

This library is licensed under `MIT License`. Read [LICENSE](LICENSE) for more info.