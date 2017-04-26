#version 430 core

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec4 VertexColor;

out vec4 color;

uniform mat4 Model, View, Projection;

void main()
{
	mat4 MVP = Projection * View * Model;
	gl_Position = MVP * vec4(VertexPosition, 1);
	color = VertexColor;
}
