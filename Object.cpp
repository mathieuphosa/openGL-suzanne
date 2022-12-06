#include "Object.h"

void Object::load_obj(string file) {
	vector<glm::vec4> v;
	vector<glm::vec2> vt;
	vector<glm::vec3> vn;
	vector<vector<GLushort>> f; // [[ , , ], [ , , ], [ , , ], ...]
	// 1) read file data into v, vt, vn
	ifstream in(file, ios::in);
	if (!in) { cerr << "Cannot open " << file << endl; exit(1); }
	string line;

	while (getline(in, line)) {

		if (line.substr(0, 2) == "v ") { // vertex data
			istringstream s(line.substr(2));
			glm::vec4 v4; s >> v4.x; s >> v4.y; s >> v4.z; v4.w = 1.0f;
			v.push_back(v4);
		}

		if (line.substr(0, 2) == "vt") { // vertex data
			istringstream s(line.substr(3));
			glm::vec3 v2; s >> v2.x; s >> v2.y;
			vt.push_back(v2);
		}

		if (line.substr(0, 2) == "vn") { // vertex data
			istringstream s(line.substr(3));
			glm::vec3 v3; s >> v3.x; s >> v3.y; s >> v3.z;
			vn.push_back(v3);
		}

		if (line.substr(0, 2) == "f ") { // vertex data
			istringstream s(line.substr(2));
			for (size_t i = 0; i < 3; i++)
			{
				string a;
				s >> a;
				vector<GLushort> glus;
				string token;
				istringstream tokenStream(a);
				while (getline(tokenStream, token, '/'))
				{
					//tokens.push_back(token);
					glus.push_back(stoi(token));
				}
				f.push_back(glus);
			}
		}
	}

	for (size_t i = 0; i < f.size(); i++)
	{
		mesh_data.push_back(v[f[i][0] - 1].x);
		mesh_data.push_back(v[f[i][0] - 1].y);
		mesh_data.push_back(v[f[i][0] - 1].z);
		mesh_data.push_back(1.0);

		// vt.u, vt.v
		mesh_data.push_back(vt[f[i][1] - 1].x);
		mesh_data.push_back(vt[f[i][1] - 1].y);

		// vn.x, vn.y, vn.z
		mesh_data.push_back(vn[f[i][2] - 1].x);
		mesh_data.push_back(vn[f[i][2] - 1].y);
		mesh_data.push_back(vn[f[i][2] - 1].z);
	}
}

void Object::binding() {
	glGenVertexArrays(1, &vao); glBindVertexArray(vao);
	glGenBuffers(1, &vbo); glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh_data.size() * sizeof(GLfloat), &mesh_data[0],
		GL_STATIC_DRAW);
}

void Object::draw(GLuint program) {
	GLuint attribute;
	attribute = glGetAttribLocation(program, "v_coord"); glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
	attribute = glGetAttribLocation(program, "v_texcoord"); glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4 * sizeof(GLfloat)));
	attribute = glGetAttribLocation(program, "v_normal"); glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	attribute = glGetAttribLocation(program, "lightColor"); glEnableVertexAttribArray(attribute);
	glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glm::vec3 light = glm::vec3(1.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(program, "lightColor"), light.x, light.y, light.z);
}

void Object::cleanUp() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}