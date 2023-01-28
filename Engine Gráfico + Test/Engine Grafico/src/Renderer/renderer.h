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

#include "Camera.h"
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
	Camera camera;
	void Draw(unsigned int *indices, float *vertices, glm::mat4 _trsmatrix, int shapeType);
	void CreateShader();
	void initRender(unsigned int vao, unsigned int vbo, unsigned int ibo);
	unsigned int shaderId;
	unsigned int textureShaderId;
	unsigned int  CreateShader(const char* vertexShader, const char* fragmentShader);

	void GenerateVAO(unsigned int& vao);
	void BindVAO(unsigned int& vao);
	void BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount);
	void BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount);
	void UnbindBuffers();
	void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);
	void CreateAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition);
	void SetTexAttribPointer();
	void DrawSprite(unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmount, glm::mat4 model, unsigned int* indices);
};
#endif // !RENDERER_H