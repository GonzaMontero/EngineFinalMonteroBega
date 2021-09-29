#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Export.h"
#include "Entity.h"

class ENGINE_API Entity2D: public Entity {
public:
	Entity2D(Renderer* _renderer);
};
#endif // !ENTITY2D_H
