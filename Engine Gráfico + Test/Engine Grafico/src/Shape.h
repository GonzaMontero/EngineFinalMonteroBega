#ifndef SHAPE_H
#define SHAPE_H

#include "Export.h"
#include "Entity2D.h"

class ENGINE_API Shape: public Entity2D {
public:
	float vertexs[18] = {
		//X     Y     Z     R      G    B
	   -0.5f,   -0.5f, 0.0f, color.R, color.G, color.B,
		0.5f,   -0.5f, 0.0f, color.R, color.G, color.B,
		0.0f,  0.375f, 0.0f, color.R, color.G, color.B
	};

	unsigned int indices[3] = {
		0,1,2
	};

	Shape(Renderer* _renderer);
	unsigned int vbo; // vertex buffer object  //  Guarda los arrays de vertices, basicamente, cada punto de la shape (y en este caso color tambien)
	unsigned int ibo;  // index buffer object  //  Guarda un array de los indices/elementos, basicamente clasifica los vertices para que al dibujar figuras que usan el mismo vertice no tenga que repetirlo
	unsigned int vao; // vertex array object   //  Buffer interno de openGL 
	Color color;
	void Init(Color newColor);
	void UpdateColor(Color newColor);
	void EpilepsyMode();
	void Draw();
};
#endif // !SHAPE_H
