#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Export.h"
#include "Entity2D.h"

class ENGINE_API CollisionManager {
public:
	CollisionManager();
	
	void CheckCollisions();

};
#endif // !CAMERA_H