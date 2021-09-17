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
	void DrawTriangle(CVec4 pos1, CVec4 pos2, CVec4 pos3);
	int i;
	unsigned int buffer;

};

#endif // !RENDERER_H