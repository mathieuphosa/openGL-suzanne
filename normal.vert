#version 430
in vec4 v_coord;
in vec2 v_texcoord;
in vec3 v_normal;

uniform mat4 MVP;
uniform mat3 NM; //Normal Matrix

out vec4 color;
out vec2 texcoord;

void main()
{
	// pass texcoord to fragment shader (not used for the moment)
	texcoord = v_texcoord;

	//display normals
	vec3 N = normalize(NM * v_normal);
	color = vec4(abs(N), 1.0f);

	gl_Position = MVP*v_coord;
}