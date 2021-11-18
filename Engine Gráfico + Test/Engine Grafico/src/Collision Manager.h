#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Export.h"
#include "Entity2D.h"
#include "glm/glm.hpp"

class ENGINE_API CollisionManager {
public:
	CollisionManager();
	
	bool CheckAABBCollisions(Entity2D* one, Entity2D* two);
	//bool CheckCircleObjectCollisions(Entity2D* one, BallObject* two);
};
#endif // !CAMERA_H