#version 460 core
uniform vec2 u_resolution;
uniform float u_time;
uniform vec2 cursorPos;

uniform sampler2D ourTexture;
uniform sampler2D smileytexture;

in vec3 Position;
in vec2 texCoord;

out vec4 FragColor;	

void main() {
	vec2 flippedCPos = vec2(cursorPos.x, u_resolution.y - cursorPos.y);
	vec2 diff = (flippedCPos - gl_FragCoord.xy) / u_resolution;
	float red = (sin(diff.x) + 1) * 0.5;
	float green = (sin(diff.y) + 1) * 0.5;
	float blue =  (sin(diff.x + diff.y + 3.14) + 1) * 0.5;
 	FragColor = vec4(red,green, blue, 1.0);
//	FragColor = mix(texture(ourTexture, texCoord), texture(smileytexture, texCoord), 0.5) * vec4(red, green, blue, 1.0);
};