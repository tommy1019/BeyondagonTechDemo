#version 330

in vec3 position;

uniform mat4 projection;

void main()
{
    gl_Position = vec4(position, 1) * projection;
}
