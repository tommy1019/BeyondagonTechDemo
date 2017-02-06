#version 330

in vec2 textureCoord;
in vec3 normal;
out vec4 fragColor;

uniform sampler2D tex;

void main() 
{
    float dirLight = max(dot(normal, vec3(1, 1, -1)), 0);

    //fragColor = vec4(normal, 0)
    fragColor = texture(tex, textureCoord) * dirLight;
}
