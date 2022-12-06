//#include <GL/glew.h>
//#include <GL/glut.h>
//#include <GL/freeglut.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>
//
//#define TITLE "OpenGL"
//#define BUFFER_OFFSET(offset) ((GLvoid*)(offset))
//
//using namespace std;
//
//// Screen size
//int SCREEN_X = 1024;
//int SCREEN_Y = 768;
//
//// Interaction
//int buttonPressed = -1;
//float last_x;
//float last_y;
//float angle_x = 0.0;
//float angle_y = 0.0;
//bool isSmooth = false;
//bool isCheckerized = false;
//bool isTextured = false;
//bool isGouraud = false;
//bool isPhong = false;
//bool celShader = false;
//
//// Reflectance
//float ka = 0.5f;
//float kd = 0.5f;
//float ks = 1.0f;
//float shininess = 20.0f;
//
//// Light
//float light_x = 0.0f;
//float light_y = 0.0f;
//float light_z = 1.0f;
//
//vector<GLfloat> suzanne;
//vector<GLfloat> suzanneSmooth;
//
//GLuint vaoSuzanne;
//GLuint vboSuzanne;
//
//GLuint vaoSuzanneSmooth;
//GLuint vboSuzanneSmooth;
//
//GLuint vaoCellShading;
//GLuint vboCellShading;
//
//GLuint shaderProgram;
//GLuint shaderOutline;
//
//GLuint texture;
//
//
//GLchar* readShaderSource(const char* shaderFile)
//{
//	FILE* fp;
//	fopen_s(&fp, shaderFile, "r");
//	GLchar* buf;
//	long size;
//	if (fp == NULL) return NULL;
//	fseek(fp, 0L, SEEK_END);//go to end
//	size = ftell(fp); //getsize
//	fseek(fp, 0L, SEEK_SET);//go to beginning
//	buf = (GLchar*)malloc((size + 1) * sizeof(GLchar));
//	fread(buf, 1, size, fp);
//	buf[size] = 0;
//	fclose(fp);
//	return buf;
//}
//
//GLuint initShaders(const char* vShaderFile, const char* fShaderFile)
//{
//	struct Shader {
//		const char* filename;
//		GLenum type;
//		GLchar* source;
//	} shaders[2] = {
//	{ vShaderFile, GL_VERTEX_SHADER, NULL },
//	{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
//	};
//	GLuint program = glCreateProgram();
//	for (int i = 0; i < 2; ++i) {
//		Shader& s = shaders[i];
//		s.source = readShaderSource(s.filename);
//		if (shaders[i].source == NULL) {
//			printf("Failed to read %s\n", s.filename);
//			exit(EXIT_FAILURE);
//		}
//		GLuint shader = glCreateShader(s.type);
//		glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);
//		glCompileShader(shader);
//		GLint compiled;
//		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
//		if (!compiled) {
//			printf("%s failed to compile:\n", s.filename);
//			GLint logSize;
//			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
//			char* logMsg = new char[logSize];
//			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
//			printf("%s\n", logMsg);
//			delete[] logMsg;
//			exit(EXIT_FAILURE);
//		}
//		delete[] s.source;
//		glAttachShader(program, shader);
//	}
//	/* linkand errorcheck */
//	glLinkProgram(program);
//	GLint linked;
//	glGetProgramiv(program, GL_LINK_STATUS, &linked);
//	if (!linked) {
//		printf("Shaderprogram failed to link:\n");
//		GLint logSize;
//		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
//		char* logMsg = new char[logSize];
//		glGetProgramInfoLog(program, logSize, NULL, logMsg);
//		printf("%s\n", logMsg);
//		delete[] logMsg;
//		exit(EXIT_FAILURE);
//	}
//	/* use program object*/
//	glUseProgram(program);
//	return program;
//}
//
//GLuint createTexureChecker() {
//	const int CHECKERSIZE = 256;
//	float* checkerImage = new float[CHECKERSIZE * CHECKERSIZE * 4];
//	int i, j; int c;
//	for (i = 0; i < CHECKERSIZE; i++)
//		for (j = 0; j < CHECKERSIZE; j++) {
//			c = ((i & 0x8) == 0) ^ ((j & 0x8) == 0); // one square = 8 pixels
//			checkerImage[4 * (i * CHECKERSIZE + j)] = (GLfloat)c;
//			checkerImage[4 * (i * CHECKERSIZE + j) + 1] = (GLfloat)c;
//			checkerImage[4 * (i * CHECKERSIZE + j) + 2] = (GLfloat)c;
//			checkerImage[4 * (i * CHECKERSIZE + j) + 3] = (GLfloat)1.0f;
//		}
//	GLuint texture;
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERSIZE, CHECKERSIZE, 0, GL_RGBA, GL_FLOAT, checkerImage);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	delete[] checkerImage;
//	return texture;
//}
//
//GLuint loadTextureFromBMP(const char* filename, int width, int height) {
//	GLuint texture = 0; unsigned char* data;
//	FILE* file; errno_t err;
//	if ((err = fopen_s(&file, filename, "rb")) != 0) printf("Error: Texture was not opened.\n");
//	else {
//		data = (unsigned char*)malloc(width * height * 3);
//		fread(data, width * height * 3, 1, file);
//		fclose(file);
//		for (int i = 0; i < width * height; ++i) { // bmp files are encoded BGR and not RGB
//			int index = i * 3; unsigned char B, R;
//			B = data[index]; R = data[index + 2];
//			data[index] = R; data[index + 2] = B;
//		}
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
//		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
//		free(data);
//	}
//	return texture;
//}
//
//void load_obj(const char* filename, vector<GLfloat>& mesh_data, vector<GLfloat>& smooth_data) {
//
//	vector<glm::vec4> v;
//	vector<glm::vec2> vt;
//	vector<glm::vec3> vn;
//	vector<vector<GLushort>> f; // [[ , , ], [ , , ], [ , , ], ...]
//	// 1) read file data into v, vt, vn
//	ifstream in(filename, ios::in);
//	if (!in) { cerr << "Cannot open " << filename << endl; exit(1); }
//	string line;
//	vector<glm::vec3> nvm;
//
//	while (getline(in, line)) {
//
//		if (line.substr(0, 2) == "v ") { // vertex data
//			istringstream s(line.substr(2));
//			glm::vec4 v4; s >> v4.x; s >> v4.y; s >> v4.z; v4.w = 1.0f;
//			v.push_back(v4);
//			nvm.push_back(glm::vec3(0, 0, 0));
//		}
//
//		if (line.substr(0, 2) == "vt") { // vertex data
//			istringstream s(line.substr(3));
//			glm::vec3 v2; s >> v2.x; s >> v2.y;
//			vt.push_back(v2);
//		}
//
//		if (line.substr(0, 2) == "vn") { // vertex data
//			istringstream s(line.substr(3));
//			glm::vec3 v3; s >> v3.x; s >> v3.y; s >> v3.z;
//			vn.push_back(v3);
//		}
//
//		if (line.substr(0, 2) == "f ") { // vertex data
//			istringstream s(line.substr(2));
//			for (size_t i = 0; i < 3; i++)
//			{
//				string a;
//				s >> a;
//				std::vector<GLushort> glus;
//				std::string token;
//				std::istringstream tokenStream(a);
//				while (std::getline(tokenStream, token, '/'))
//				{
//					//tokens.push_back(token);
//					glus.push_back(std::stoi(token));
//				}
//				f.push_back(glus);
//			}
//		}
//	}
//
//	for (size_t i = 0; i < f.size(); i++)
//	{
//		mesh_data.push_back(v[f[i][0] - 1].x);
//		mesh_data.push_back(v[f[i][0] - 1].y);
//		mesh_data.push_back(v[f[i][0] - 1].z);
//		mesh_data.push_back(1.0);
//
//		// vt.u, vt.v
//		mesh_data.push_back(vt[f[i][1] - 1].x);
//		mesh_data.push_back(vt[f[i][1] - 1].y);
//
//		// vn.x, vn.y, vn.z
//		mesh_data.push_back(vn[f[i][2] - 1].x);
//		mesh_data.push_back(vn[f[i][2] - 1].y);
//		mesh_data.push_back(vn[f[i][2] - 1].z);
//
//		nvm[f[i][0] - 1] += vn[f[i][2] - 1];
//	}
//
//	for (int i = 0; i < nvm.size(); i++) {
//		nvm[i] = glm::normalize(nvm[i]);
//	}
//
//	for (size_t i = 0; i < f.size(); i++)
//	{
//		smooth_data.push_back(v[f[i][0] - 1].x);
//		smooth_data.push_back(v[f[i][0] - 1].y);
//		smooth_data.push_back(v[f[i][0] - 1].z);
//		smooth_data.push_back(1.0);
//
//		// vt.u, vt.v
//		smooth_data.push_back(vt[f[i][1] - 1].x);
//		smooth_data.push_back(vt[f[i][1] - 1].y);
//
//		// vn.x, vn.y, vn.z
//		smooth_data.push_back(nvm[f[i][0] - 1].x);
//		smooth_data.push_back(nvm[f[i][0] - 1].y);
//		smooth_data.push_back(nvm[f[i][0] - 1].z);
//	}
//}
//
//void updateMVP(GLuint program) {
//	glm::mat4 Projection = glm::perspective(45.0f, float(SCREEN_X / SCREEN_Y), 0.1f, 20.0f);
//	glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//	//glm::mat4 Model = ...; // translate, rotate, scale
//	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f));
//	Model = glm::rotate(Model, angle_y, glm::vec3(1, 0, 0));
//	Model = glm::rotate(Model, angle_x, glm::vec3(0, 1, 0));
//	glm::mat4 MV = View * Model;
//	glm::mat4 MVP = Projection * MV;
//	glm::mat3 NM = glm::transpose(glm::inverse(glm::mat3(MV)));
//	glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, GL_FALSE, &MVP[0][0]);
//	glUniformMatrix3fv(glGetUniformLocation(program, "NM"), 1, GL_FALSE, &NM[0][0]);
//	if (isGouraud || isPhong) {
//		glUniform1f(glGetUniformLocation(program, "ka"), ka);
//		glUniform1f(glGetUniformLocation(program, "kd"), kd);
//		glUniform1f(glGetUniformLocation(program, "ks"), ks);
//		glUniform1f(glGetUniformLocation(program, "shininess"), shininess);
//		glUniform3f(glGetUniformLocation(program, "light_source"), light_x, light_y, light_z);
//		glUniformMatrix3fv(glGetUniformLocation(program, "MV"), 1, GL_FALSE, &MV[0][0]);
//	}
//}
//
//void shaderPlumbing(GLuint program)
//{
//	GLuint attribute;
//	attribute = glGetAttribLocation(program, "v_coord");
//	glEnableVertexAttribArray(attribute);
//	glVertexAttribPointer(attribute, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)0);
//
//	attribute = glGetAttribLocation(program, "v_texcoord");
//	glEnableVertexAttribArray(attribute);
//	glVertexAttribPointer(attribute, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(4*sizeof(GLfloat)));
//
//	attribute = glGetAttribLocation(program, "v_normal");
//	glEnableVertexAttribArray(attribute);
//	glVertexAttribPointer(attribute, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//}
//
//void init() {
//	// Window init
//	glClearColor(1.0, 1.0, 1.0, 1.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-3.0, 3.0, -3.0, 3.0, -2.0, 2.0);
//	glViewport(0, 0, SCREEN_X, SCREEN_Y);
//
//	glEnable(GL_DEPTH_TEST);
//	load_obj("suzanne.obj", suzanne, suzanneSmooth);
//
//	// vao init
//	glGenVertexArrays(1, &vaoSuzanne);
//	glBindVertexArray(vaoSuzanne);
//
//	// vbo init
//	glGenBuffers(1, &vboSuzanne);
//	glBindBuffer(GL_ARRAY_BUFFER, vboSuzanne);
//
//	glBufferData(GL_ARRAY_BUFFER, suzanne.size() * sizeof(GLfloat), &suzanne[0], GL_STATIC_DRAW);
//
//	if (isCheckerized || isTextured) shaderProgram = initShaders("normal.vert", "texture.frag");
//	else
//	{
//		if (isGouraud) shaderProgram = initShaders("gouraudShader.vert", "normal.frag");
//		else
//		{
//			if (isPhong) shaderProgram = initShaders("phongShader.vert", "phongShader.frag");
//			else shaderProgram = initShaders("normal.vert", "normal.frag");
//		}
//	}
//	shaderPlumbing(shaderProgram);
//
//	// vao init
//	glGenVertexArrays(1, &vaoSuzanneSmooth);
//	glBindVertexArray(vaoSuzanneSmooth);
//
//	// vbo init
//	glGenBuffers(1, &vboSuzanneSmooth);
//	glBindBuffer(GL_ARRAY_BUFFER, vboSuzanneSmooth);
//
//	updateMVP(shaderProgram);
//
//	glBufferData(GL_ARRAY_BUFFER, suzanneSmooth.size() * sizeof(GLfloat), &suzanneSmooth[0], GL_STATIC_DRAW);
//
//	if (isCheckerized || isTextured) shaderProgram = initShaders("normal.vert", "texture.frag");
//	else
//	{
//		if (isGouraud) shaderProgram = initShaders("gouraudShader.vert", "normal.frag");
//		else
//		{
//			if (isPhong) shaderProgram = initShaders("phongShader.vert", "phongShader.frag");
//			else
//			{
//				if (celShader)
//				{
//					shaderProgram = initShaders("phongShader.vert", "phongShader.frag");
//					// vao init
//					glGenVertexArrays(1, &vaoCellShading);
//					glBindVertexArray(vaoCellShading);
//
//					// vbo init
//					glGenBuffers(1, &vboCellShading);
//					glBindBuffer(GL_ARRAY_BUFFER, vboCellShading);
//
//					updateMVP(shaderOutline);
//
//					glBufferData(GL_ARRAY_BUFFER, suzanneSmooth.size() * sizeof(GLfloat), &suzanneSmooth[0], GL_STATIC_DRAW);
//					shaderOutline = initShaders("celOutline.vert", "passthrough.frag");
//					shaderPlumbing(shaderOutline);
//				}
//				else shaderProgram = initShaders("normal.vert", "normal.frag");
//			}
//		}
//	}
//	shaderPlumbing(shaderProgram);
//}
//
//void cleanup() {
//	// VAO cleanup
//	glDeleteVertexArrays(1, &vaoSuzanne);
//	glDeleteVertexArrays(1, &vaoSuzanneSmooth);
//	glDeleteVertexArrays(1, &vaoCellShading);
//
//	// VBO cleanup
//	glDeleteBuffers(1, &vboSuzanne);
//	glDeleteBuffers(1, &vboSuzanneSmooth);
//	glDeleteBuffers(1, &vboCellShading);
//}
//
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// initiate vertex shader
//	if (celShader) {
//		glDisable(GL_DEPTH_TEST);
//		glUseProgram(shaderOutline);
//		updateMVP(shaderOutline);
//		glBindVertexArray(vaoCellShading);
//		glDrawArrays(GL_TRIANGLES, 0, suzanne.size() / 9);
//
//		glEnable(GL_DEPTH_TEST);
//		glUseProgram(shaderProgram);
//	}
//
//	updateMVP(shaderProgram);
//	glBindVertexArray(isSmooth ? vaoSuzanneSmooth : vaoSuzanne);
//	glDrawArrays(GL_TRIANGLES, 0, suzanne.size()/9);
//
//	glutSwapBuffers();
//}
//
//void motionfunc(int x, int y)
//{
//	if (buttonPressed == 0)
//	{
//		angle_x += (-(x - last_x)) * 0.01;
//		angle_y += (-(y - last_y)) * 0.01;
//		last_x = x;
//		last_y = y;
//	}
//	else if(buttonPressed == 2)
//	{
//		light_x += (x - last_x) *0.01;
//		light_y += (y - last_y) *0.01;
//		last_x = x;
//		last_y = y;
//	}
//	if (buttonPressed != -1)
//	{
//		glutDisplayFunc(display);
//		glutPostRedisplay();
//	}
//}
//
//void mousefunc(int button, int state, int x, int y) {
//	if (state == 0)
//	{
//		buttonPressed = button;
//		last_x = x;
//		last_y = y;
//	}
//	else buttonPressed = -1;
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//	switch (key) {
//	case 27: case 'q': case 'Q':
//		exit(EXIT_SUCCESS);
//		return;
//	case 's': case 'S':
//		isSmooth = !isSmooth;
//		display();
//		return;
//	case 't': case 'T':
//		isTextured = !isTextured;
//		isCheckerized = false;
//		celShader = false;
//		texture = loadTextureFromBMP("texture.bmp", 720, 405);
//		break;
//	case 'c': case 'C':
//		isCheckerized = !isCheckerized;
//		isTextured = false;
//		celShader = false;
//		texture = createTexureChecker();
//		break;
//	case 'g': case 'G':
//		isGouraud = !isGouraud;
//		isPhong = false;
//		celShader = false;
//		break;
//	case 'p': case 'P':
//		isPhong = !isPhong;
//		isGouraud = false;
//		celShader = false;
//		break;
//	case 'a': case 'A':
//		ka = ka == 0.0f ? 0.5f : 0.0f;
//		break;
//	case 'd': case 'D':
//		kd = kd == 0.0f ? 0.5f : 0.0f;
//		break;
//	case 'r': case 'R':
//		ks = ks == 0.0f ? 1.0f : 0.0f;
//		break;
//	case 'o': case 'O':
//		celShader = !celShader;
//		if (celShader)
//		{
//			isPhong = false;
//			isGouraud = false;
//			isCheckerized = false;
//			isTextured = false;
//			isSmooth = true;
//		}
//		break;
//	}
//	init();
//	display();
//}
//
//int main(int argc, char** argv)
//{
//	// Init Glut
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//	glutInitWindowSize(SCREEN_X, SCREEN_Y);
//	glutCreateWindow(TITLE);
//	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
//
//	GLenum err = glewInit();
//	if (GLEW_OK != err)
//	{
//		// glewInit failed
//		fprintf(stderr, "Error :%s\n", glewGetErrorString(err));
//		exit(EXIT_FAILURE);
//	}
//	fprintf(stdout, "Using GLew %s\n", glewGetString(GLEW_VERSION));
//
//	init();
//
//	glutDisplayFunc(display);
//	glutKeyboardFunc(keyboard);
//	glutMouseFunc(mousefunc);
//	glutMotionFunc(motionfunc);
//
//	glutMainLoop();
//
//	cleanup();
//
//	return 0;
//}