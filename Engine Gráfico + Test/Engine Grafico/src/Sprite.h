#ifndef SPRITE_H
#define SPRITE_H


#include "Export.h"
#include "Entity2D.h"
#include"TextureImporter.h"


class ENGINE_API Sprite : public Entity2D {
private:
	int _width = 0;
	int _height = 0;
	bool _transparency;
	TextureImporter* _texImporter;
	unsigned int vbo; // vertex buffer object  //  Guarda los arrays de vertices, basicamente, cada punto de la shape (y en este caso color tambien)
	unsigned int ebo;  // index buffer object  //  Guarda un array de los indices/elementos, basicamente clasifica los vertices para que al dibujar figuras que usan el mismo vertice no tenga que repetirlo
	unsigned int vao; // vertex array object   //  Buffer interno de openGL 

	float vertexs[32] = {
		//X     Y     Z      R      G    B     U  V
		1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  1, 1,
		1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  1, 0,
		-1.0f, -1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  0, 0,
		-1.0f,  1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  0, 1
	};

	unsigned int indices[6] = {
		0,1,3,1,2,3
	};


	void LoadSprite(int width, int height, const char* path);
	void GenerateVAO();

	void BindBuffers();
	void BindTexture();
	void BindVAO();
	void BindVBO(float* vertices, int AmmountOfVertices);
	void BindEBO(unsigned int* indices, int AmmountOfIndices);

	void UnbindBuffers();
	void DeleteBuffer();

	void BlendSprite();
	void UnBlendSprite();


public:
	Sprite(bool transparency, Renderer* renderer);
	Sprite(bool transparency, const char* path, Renderer* renderer);
	~Sprite();
	void Init();
	Color color;
	void DrawSprite();
	void SetPath(const char* path);
	const char* GetPath();
};
#endif // !SHAPE_H
