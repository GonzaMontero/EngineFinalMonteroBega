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

//bool CheckCircleObjectCollisions(Entity2D* one, BallObject* two) {
//    // get center point circle first 
//    glm::vec2 center(one.Position + one.Radius);
//    // calculate AABB info (center, half-extents)
//    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
//    glm::vec2 aabb_center(
//        two.Position.x + aabb_half_extents.x,
//        two.Position.y + aabb_half_extents.y
//    );
//    // get difference vector between both centers
//    glm::vec2 difference = center - aabb_center;
//    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
//    // add clamped value to AABB_center and we get the value of box closest to circle
//    glm::vec2 closest = aabb_center + clamped;
//    // retrieve vector between center circle and closest point AABB and check if length <= radius
//    difference = closest - center;
//    return glm::length(difference) < one.Radius;
//}


