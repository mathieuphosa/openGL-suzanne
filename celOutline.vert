#version 430
in vec4 v_coord;
in vec3 v_normal;

uniform mat4 MVP;

out vec4 color;

void main()
{

	vec4 pos = v_coord + vec4(v_normal, 0.0f) * 0.05f;
	color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	gl_Position = MVP*pos;
}