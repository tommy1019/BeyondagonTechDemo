#version 330

uniform sampler2D tex;

uniform vec3 eyePos;

in vec3 vNormal;
in vec2 vTex;

out vec4 fragColor;

void main() 
{
    vec3 ambientAmt = vec3(.08, .08, .08);
    vec3 directionalLight = normalize(vec3(1, -1, -1));
    vec3 surfaceColor = texture(tex, vTex).xyz;

    vec3 ambient = ambientAmt * surfaceColor;

    float diffuseCoefficient = max(0.0, dot(vNormal, directionalLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor;

    vec3 linearColor = ambient + diffuse;
    vec3 gamma = vec3(1.0/2.2);

    fragColor = vec4(pow(linearColor, gamma), 1);
}
