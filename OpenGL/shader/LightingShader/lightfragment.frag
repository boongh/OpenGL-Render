#version 460 core
uniform vec2 u_resolution;
uniform float u_time;
uniform vec2 cursorPos;

uniform sampler2D ourTexture;
uniform sampler2D smileytexture;

uniform vec3 objectColor;
uniform vec3 ambientColor;

uniform float ambientStrength;

in vec2 texCoord;
in vec3 normal;

out vec4 FragColor;	

void main() {
	vec3 ambient = ambientStrength * ambientColor;
	vec3 result = ambient * objectColor;
	FragColor = vec4(result, 1);
};