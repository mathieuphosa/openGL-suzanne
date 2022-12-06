#version 430
in vec4 color;
in vec2 texcoord;

out vec4 fColor; //final fragment color

void main()
{
	fColor = color;
}