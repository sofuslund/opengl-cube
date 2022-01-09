#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 color;

uniform vec3 lightColor;
uniform mat4 trans;

void main()
{
    gl_Position = trans *  vec4(aPos, 1.0);
    color = lightColor;
}