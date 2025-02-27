#version 460 core
uniform vec2 u_resolution;
uniform float u_time;
uniform vec2 cursorPos;

uniform sampler2D ourTexture;
uniform sampler2D smileytexture;

uniform vec3 lightColor;

in vec3 Position;
in vec2 texCoord;

out vec4 FragColor;	

void main() {
	FragColor = vec4(lightColor, 1);
};