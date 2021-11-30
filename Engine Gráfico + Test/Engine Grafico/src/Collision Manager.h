#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "Export.h"
#include "Entity2D.h"
#include "glm/glm.hpp"

class ENGINE_API CollisionManager {
public:
	CollisionManager();
	
	bool CheckAABBCollisions(Entity2D* one, Entity2D* two);

private:
	bool ReturnIntersect(float min0,float max0,float min1,float max1);
	//bool CheckCircleObjectCollisions(Entity2D* one, BallObject* two);
};
#endif // !CAMERA_H