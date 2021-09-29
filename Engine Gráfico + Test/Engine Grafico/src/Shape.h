#ifndef SHAPE_H
#define SHAPE_H

#include "Export.h"
#include "Entity2D.h"

class ENGINE_API Shape: public Entity2D {
public:
	Shape(Renderer* _renderer);
};
#endif // !SHAPE_H
