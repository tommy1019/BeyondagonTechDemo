#version 330

in vec2 textureCoord;
in vec3 normal;
in vec3 color;

out vec4 fragColor;

uniform sampler2D tex;

void main() 
{
    float dirLight = max(dot(normal, normalize(vec3(1, 1, 1))), 0);

    //fragColor = vec4((normal.x + 1) / 2, (normal.y + 1) / 2, (normal.z + 1) / 2, 1);// * dirLight;
    fragColor = texture(tex, textureCoord) * dirLight * vec4(color, 1.0f);
}
