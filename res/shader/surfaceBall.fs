#version 330

in vec3 normal;
out vec4 fragColor;

void main() 
{
    float cosTheta = clamp(dot(normal, vec3(0, 0, 0)), 0, 1);
    fragColor = vec4(1,1,0,1) * cosTheta;
}
