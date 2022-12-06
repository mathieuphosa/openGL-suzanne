#version 430
in vec4 color; //ignored
in vec2 texcoord; //the interpolated UV coordinates
uniform sampler2D tex; // the currently bound texture

out vec4 fColor; //final fragment color

void main()
{
	fColor = texture(tex, texcoord) * color;
}