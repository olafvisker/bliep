#version 330 
#define N_DIR_LIGHTS 4
#define N_POINT_LIGHTS 32

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {    
    vec3 position;
    float constant;
    float linear;
    float quadratic; 
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 v_normal;
in vec3 v_position;
in vec2 v_uv;

out vec4 f_color;

uniform vec3 view_pos;
uniform int n_dir_lights;
uniform int n_point_lights;

uniform Material material;
uniform DirLight dirlight[N_DIR_LIGHTS];  
uniform PointLight pointlight[N_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 view_dir);  
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 v_position, vec3 view_dir);  

void main() {
    vec3 norm = normalize(v_normal);
    vec3 view_dir = normalize(view_pos - v_position);

    vec3 result = vec3(0.0);

    for(int i = 0; i < n_dir_lights; i++) result += CalcDirLight(dirlight[i], norm, view_dir);
    for(int i = 0; i < n_point_lights; i++) result += CalcPointLight(pointlight[i], norm, v_position, view_dir);    

    f_color = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 view_dir) {
    vec3 light_dir = normalize(-light.direction);
    float diff = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, v_uv));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, v_uv));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, v_uv));
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 v_position, vec3 view_dir) {
    vec3 light_dir = normalize(light.position - v_position);
    float diff = max(dot(normal, light_dir), 0.0);
    vec3 reflect_dir = reflect(-light_dir, normal);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
    float distance    = length(light.position - v_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, v_uv));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, v_uv));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, v_uv));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 