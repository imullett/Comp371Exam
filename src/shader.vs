#version 330 core					

layout (location = 0) in vec3 aPos;									

out vec3 vertexColor;									

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform float r;
uniform float rg;
uniform float rgb;

void main()											
{
	gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);	
	vertexColor = vec3(r, rg, rgb);							
}														