#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec2 aTextCoord;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

out vec4 vColor;

void main(){
    gl_Position = proj * view * model * vec4(aPos,1.0);
    vColor = aColor;
}