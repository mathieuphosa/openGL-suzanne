#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Object
{
public:
	void load_obj(string file);
	void binding();
	void draw(GLuint program);
	void cleanUp();
	void setVShaderFile(char* file) { vShaderFile = file; }
	void setFShaderFile(char* file) { fShaderFile = file; }
	char* getVShaderFile() { return vShaderFile; }
	char* getFShaderFile() { return fShaderFile; }

private:
	GLuint vao;
	GLuint vbo;
	vector<glm::vec4> positions;
	vector<glm::vec4> colors;
	vector<GLfloat> mesh_data;
	char* vShaderFile;
	char* fShaderFile;

};

