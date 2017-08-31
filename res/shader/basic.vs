#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;

out vec3 vNormal;
out vec2 vTex;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
    gl_Position = vec4(position, 1) * projection;
    vNormal = normal;
    vTex = texture;
}
