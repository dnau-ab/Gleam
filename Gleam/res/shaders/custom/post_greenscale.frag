#version 330 core

out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D lightingTex;

void main()
{
	vec3 color = texture(lightingTex, texCoord).rgb;
	
	const float NUM_SHADES = 6.0f;
	float shade = (color.x + color.y + color.z) / 3.0f;
	shade = (floor(shade * NUM_SHADES)) / NUM_SHADES;
	
	fragColor = vec4(0.0f, shade * 1.5, 0.0f, 1.0f);
}