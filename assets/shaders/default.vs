#version 330 

layout (location = 0) in vec3 l_position;
layout (location = 1) in vec3 l_normal;
layout (location = 2) in vec2 l_uv;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal;

void main() {
    gl_Position = projection * view * model * vec4(l_position, 1.0);
    
    v_position = vec3(model * vec4(l_position, 1.0));
    v_normal = normal * l_normal;
    v_uv = l_uv;
}