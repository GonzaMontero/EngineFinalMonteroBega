#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Export.h"
#include "Entity2D.h"

class ENGINE_API CollisionManager {
public:
	CollisionManager();
	
	bool CheckCollisions(Entity2D one, Entity2D two);

};
#endif // !CAMERA_H