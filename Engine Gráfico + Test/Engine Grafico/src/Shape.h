#ifndef SHAPE_H
#define SHAPE_H

#include "Export.h"
#include "Entity2D.h"

class ENGINE_API Shape: public Entity2D {
public:
	
	Shape(Renderer* _renderer);
	unsigned int vbo; // vertex buffer object
	unsigned int ibo;  // index buffer object
	unsigned int vao; // vertex array object
	void Init();
	void Draw();
};
#endif // !SHAPE_H
