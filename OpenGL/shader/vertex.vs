#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 atexCoord;

out vec3 Position;
out vec2 texCoord;

uniform mat4 trans;

void main()
{
   gl_Position = trans * vec4(aPos, 1.0);
   texCoord = atexCoord;
};
