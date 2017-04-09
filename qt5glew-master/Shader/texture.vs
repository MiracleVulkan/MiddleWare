#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertex_color;
out vec3 mycolor;
void main(){
gl_Position = vec4(vertexPosition_modelspace, 1);
mycolor = vertex_color;
}