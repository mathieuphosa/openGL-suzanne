#version 430
in vec4 v_coord;
in vec2 v_texcoord;
in vec3 v_normal;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 NM; //Normal Matrix

out vec3 P;
out vec3 N;
out vec4 color;
out vec2 texcoord;

void main()
{
	// pass texcoord to fragment shader (not used for the moment)
	texcoord = v_texcoord;

	P = vec3(MV*v_coord);
	N = normalize(NM * v_normal);

	gl_Position = MVP*v_coord;
}