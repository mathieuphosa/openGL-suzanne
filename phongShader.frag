#version 430
in vec3 P;
in vec2 texcoord;
in vec3 N;

uniform mat4 MVP;

uniform vec3 light_source;
uniform float ka;
uniform float kd;
uniform float ks;
uniform float shininess;

out vec4 fColor; // final color

void main()
{

	vec3 light_vector = normalize(light_source - P);

	// Ambient color
	vec3 ambient = ka * vec3(1.0f, 0.0f, 0.0f);

	// Diffuse color
	vec3 diffuse = kd * vec3(0.0f, 1.0f, 0.0f) * max(dot(N,light_vector), 0.0f);

	// Specular lighting
	float facing = (dot(normalize(N), light_vector)) > 0 ? 1 : 0;
	vec3 reflection = reflect(-light_vector, N);
	
	vec3 viewportPosition = vec3(MVP * vec4(0.0f, 0.0f, 0.0f, 1.0f));
	vec3 viewpoint = normalize(viewportPosition - P);
	vec3 specular = ks * vec3(0.0f, 0.0f, 1.0f) * facing * pow(max(dot(reflection, viewpoint), 0.0f), shininess);

	fColor = vec4(ambient + diffuse + specular, 1.0f);
}