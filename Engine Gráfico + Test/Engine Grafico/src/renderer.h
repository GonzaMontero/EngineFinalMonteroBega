#ifndef RENDERER_H
#define RENDERER_H
#include "export.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "Global.h"

enum ShadersType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};
struct ShadersSource
{
	string vertexSource;
	string fragmentSource;
};

class ENGINE_API Renderer {
public:
	Renderer();
	~Renderer();
	void DrawTriangle(unsigned int *indices, float *vertices, glm::mat4 _trsmatrix);
	void BindBuffers(unsigned int &vao, unsigned int &vbo, unsigned int &ibo);
	void initRender();
	unsigned int shaderId;
	unsigned int  CreateShader(const char* vertexShader, const char* fragmentShader);
};
#endif // !RENDERER_H