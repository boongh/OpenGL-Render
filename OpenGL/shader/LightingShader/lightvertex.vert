#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 TextureCord;
layout (location = 3) in vec3 DiffuseColor;
layout (location = 4) in vec3 Specular;
layout (location = 5) in float reflectivity;
layout (location = 6) in float Brightness;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float ambientStrength;

out vec2 texCoord;
out vec3 normal;

void main()
{
   gl_Position = projection * view * model * vec4(aPos, 1.0);
   normal = aNormal;
};
