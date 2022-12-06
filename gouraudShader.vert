#version 430
in vec4 v_coord;
in vec2 v_texcoord;
in vec3 v_normal;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat3 NM; //Normal Matrix

uniform vec3 light_source;
uniform float ka;
uniform float kd;
uniform float ks;
uniform float shininess;

out vec4 color;
out vec2 texcoord;

void main()
{
	// pass texcoord to fragment shader (not used for the moment)
	texcoord = v_texcoord;

	vec3 position = vec3(MV*v_coord);
	vec3 light_vector = normalize(light_source - position);

	// Normals
	vec3 N = normalize(NM * v_normal);

	// Ambient color
	vec3 ambient = ka * vec3(1.0f, 0.0f, 0.0f);

	// Diffuse color
	vec3 diffuse = kd * vec3(0.0f, 1.0f, 0.0f) * max(dot(N,light_vector), 0.0f);

	// Specular lighting
	float facing = (dot(N, light_vector)) > 0 ? 1 : 0;
	vec3 reflection = reflect(-light_vector, N);
	
	vec3 viewportPosition = vec3(MVP * vec4(0.0f, 0.0f, 0.0f, 1.0f));
	vec3 viewpoint = normalize(viewportPosition - position);
	vec3 specular = ks * vec3(0.0f, 0.0f, 1.0f) * facing * pow(max(dot(reflection, viewpoint), 0.0f), shininess);

	color = vec4(ambient + diffuse + specular, 1.0f);

	gl_Position = MVP*v_coord;
}