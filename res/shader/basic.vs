#version 330

in vec3 position;
out vec3 vPosition;

uniform vec3 t;

void main()
{
    vPosition = position * vec3(0.1, 0.1, 0.1) + t;
}
