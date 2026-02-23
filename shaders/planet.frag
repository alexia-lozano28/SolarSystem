#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
uniform bool isSun;
uniform sampler2D texture1;

uniform vec3 lightPos;   // posición del Sol
uniform vec3 viewPos;    // posición de la cámara


void main()
{
    
    vec3 color = texture(texture1, TexCoords).rgb;
    if(isSun){
        FragColor = vec4(color, 1.0);
        return;
    }

    // Ambiente
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * color;

    // Difusa
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * color;

    // Especular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}