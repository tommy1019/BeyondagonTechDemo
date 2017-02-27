#version 330

in vec3 position;
in vec2 textureCoord;
in vec3 normal;
in vec3 color;

out vec4 fragColor;

uniform sampler2D tex;

uniform vec3 eyePos;

void main() 
{
    vec3 ambientAmt = vec3(.05, .05, .05);
    vec3 directionalLight = normalize(vec3(1, -1, -1));
    vec3 specularColor = vec3(1, 1, 1);
    float materialShininess = 20;
    
    vec3 surfaceColor = texture(tex, textureCoord).xyz;
    vec3 toEye = normalize(eyePos - position);
    
    vec3 ambient = ambientAmt * surfaceColor;
    float diffuseCoefficient = max(0.0, dot(normal, directionalLight));
    vec3 diffuse = diffuseCoefficient * surfaceColor;
    
    float specularCoefficient = 0.0;
    //if(diffuseCoefficient > 0.0)
        specularCoefficient = pow(max(0.0, -dot(toEye, reflect(-directionalLight, normal))), materialShininess);
    vec3 specular = specularCoefficient * specularColor;
    
    vec3 linearColor = ambient + diffuse + specular;
    vec3 gamma = vec3(1.0/2.2);
    fragColor = vec4(pow(linearColor, gamma), 1);
}
