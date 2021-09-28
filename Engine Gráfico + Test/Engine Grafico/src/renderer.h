#ifndef RENDERER_H
#define RENDERER_H
#include "export.h"

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
	void DrawTriangle(CVec3 pos1, CVec3 pos2, CVec3 pos3);
	void BindBuffers();
	void initRender();
	unsigned int vbo; // vertex buffer object
	unsigned int ibo;  // index buffer object
	unsigned int vao; // vertex array object
	unsigned int shaderId;
	unsigned int  CreateShader(const char* vertexShader, const char* fragmentShader);

	float vertexs[18] = {
		  //X     Y     Z     R      G    B
		 -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		  0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[3] = {
		0,1,2
	};
};

#endif // !RENDERER_H