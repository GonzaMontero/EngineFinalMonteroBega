#ifndef SPRITE_H
#define SPRITE_H


#include "Export.h"
#include "Entity2D.h"
#include"TextureImporter.h"
#include "Animation.h"
#include "Time.h"

struct UV {
	float u;
	float v;
};

class ENGINE_API Sprite : public Entity2D {
private:
	int _width = 0;
	int _height = 0;
	int _nrChannels;
	unsigned int _texture;
	const char* _path;
	bool _transparency;
	int _size;
	int _currentFrame;
	int _previousFrame;

	TextureImporter* _texImporter;
	Animation* anim;
	UV uv[4];


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
	Sprite();
	~Sprite();

	
	void setAnimation(Animation* animation);
	Animation* getAnimation();	
	void setAnimCoords(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3);
	void updateAnimation(Time& time);
	void blendSprite();
	void unblendSprite();
	void SetCurrentAnimationIndex(int currentAnimation);

	void Init();
	Color color;
	void DrawSprite();
	void SetPath(const char* path);
	const char* GetPath();
};

#endif // !SHAPE_H
