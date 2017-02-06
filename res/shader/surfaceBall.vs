#version 330

in vec3 position;

uniform mat4 projection;
uniform mat4 transform;

out vec3 vPosition;

void main()
{
    vPosition = (vec4(position, 1) * projection).xyz;
}
