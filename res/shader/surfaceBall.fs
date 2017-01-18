#version 330

in vec2 textureCoord;
in vec3 normal;
out vec4 fragColor;

uniform sampler2D tex;

void main() 
{
    fragColor = texture(tex, textureCoord);
}
