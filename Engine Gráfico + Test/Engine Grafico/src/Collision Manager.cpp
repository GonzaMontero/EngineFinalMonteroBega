#include "Collision Manager.h"

CollisionManager::CollisionManager(){

}

bool CollisionManager::CheckAABBCollisions(Entity2D* one, Entity2D* two){

	glm::vec2 oneScale(one->scalation.x, one->scalation.y);
	glm::vec2 onePos(one->position.x, one->position.y);

	glm::vec2 twoScale(two->scalation.x, two->scalation.y);
	glm::vec2 twoPos(two->position.x, two->position.y);

	bool collisionX = onePos.x + oneScale.x >= twoPos.x &&
		twoPos.x + twoScale.x >= onePos.x;

	bool collisionY = onePos.y + oneScale.y >= twoPos.y &&
		twoPos.y + twoScale.y >= onePos.y;

	return collisionX && collisionY;
}