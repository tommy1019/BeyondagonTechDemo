#version 330

in vec3 position;

uniform mat4 projection;
uniform mat4 transform;

out vec3 nPosition;
out vec3 tPosition;

void main()
{
    nPosition = position;
    tPosition = (vec4(position, 1) * transform).xyz;
}
