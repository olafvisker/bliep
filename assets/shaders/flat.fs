#version 330 

out vec4 f_color;

uniform vec4 object_color = vec4(1.0);

void main() {
    f_color = object_color;
}