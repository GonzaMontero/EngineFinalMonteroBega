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
	unsigned int vbo; // vertex buffer object
	unsigned int ibo;  // index buffer object
	unsigned int vao; // vertex array object
	Color color;
	void Init(Color newColor);
	void UpdateColor(Color newColor);
	void Draw();
};
#endif // !SHAPE_H
