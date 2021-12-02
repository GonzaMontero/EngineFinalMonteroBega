#include "Collision Manager.h"

CollisionManager::CollisionManager(){

}

bool CollisionManager::CheckAABBCollisions(Entity2D* one, Entity2D* two){

	glm::vec2 oneScale(one->scalation.x, one->scalation.y);
	glm::vec2 onePos(one->position.x, one->position.y);

	glm::vec2 twoScale(two->scalation.x, two->scalation.y);
	glm::vec2 twoPos(two->position.x, two->position.y);

	bool collisionX = one->position.x + one->scalation.x >= two->position.x - (two->scalation.x)&&
		one->position.x - (one->scalation.x) <= two->position.x + (two->scalation.x);
	
	bool collisionY = one->position.y + one->scalation.y >= two->position.y - (two->scalation.y) &&
		one->position.y - one->scalation.y <= two->position.y + two->scalation.y;

	if (collisionX && collisionY)
		return true;
	else
	{
		return false;
	}

}

bool CollisionManager::ReturnIntersect(float min0, float max0, float min1, float max1) {
	return glm::max(min0, max0) >= glm::min(min1, max1) &&
		glm::min(min0, max0) <= glm::max(min1, max1);
	//Fuente : coding math (episode 14)
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


