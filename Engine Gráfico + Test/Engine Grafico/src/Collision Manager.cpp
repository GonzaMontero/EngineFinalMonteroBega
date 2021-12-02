#include "Collision Manager.h"

CollisionManager::CollisionManager() {

}

bool CollisionManager::CheckAABBCollisions(Entity2D* one, Entity2D* two) {

	glm::vec2 oneScale(one->scalation.x, one->scalation.y);
	glm::vec2 onePos(one->position.x, one->position.y);

	glm::vec2 twoScale(two->scalation.x, two->scalation.y);
	glm::vec2 twoPos(two->position.x, two->position.y);

	bool collisionX = one->position.x + one->scalation.x >= two->position.x - (two->scalation.x) &&
		one->position.x - (one->scalation.x) <= two->position.x + (two->scalation.x);

	bool collisionY = one->position.y + one->scalation.y >= two->position.y - (two->scalation.y) &&
		one->position.y - one->scalation.y <= two->position.y + two->scalation.y;

	if (collisionX && collisionY)
		return true;
	else
	{
		return false;
	}

	//return ReturnIntersect(onePos.x - (oneScale.x), onePos.x + (oneScale.x), twoPos.x - (twoScale.x), twoPos.x + (twoScale.x)) &&
	//	ReturnIntersect(onePos.y - (oneScale.y), onePos.y + (oneScale.y), twoPos.y - (twoScale.y), twoPos.y + (twoScale.y));

}

bool CollisionManager::ReturnIntersect(float min0, float max0, float min1, float max1) {
	return glm::max(min0, max0) >= glm::min(min1, max1) &&
		glm::min(min0, max0) <= glm::max(min1, max1);
	//Fuente : coding math (episode 14)
}

CollisionManager::sides CollisionManager::CheckOverlapCollisions(Entity2D* one, Entity2D* two)
{
	glm::vec2 oneScale(one->scalation.x, one->scalation.y);
	glm::vec2 onePos(one->position.x, one->position.y);

	glm::vec2 twoScale(two->scalation.x, two->scalation.y);
	glm::vec2 twoPos(two->position.x, two->position.y);

	float minX = 0.0f;
	float maxX = glm::min(onePos.x + fabs(oneScale.x), twoPos.x + fabs(twoScale.x)) - glm::max(onePos.x - fabs(oneScale.x), twoPos.x - fabs(twoScale.x));
	float overlapX = glm::max(minX, maxX);

	float minY = 0.0f;
	float maxY = glm::min(onePos.y + fabs(oneScale.y), twoPos.y + fabs(twoScale.y)) - glm::max(onePos.y - fabs(oneScale.y), twoPos.y - fabs(twoScale.y));
	float overlapY = glm::max(minY, maxY);

	if (overlapX != 0.0f && overlapY != 0.0f) {
		if (overlapX > overlapY) {
			if (twoPos.y < 0 && onePos.y < twoPos.y || onePos.y > 0 && onePos.y < twoPos.y) {
				std::cout << "BOTTOM" << std::endl;
				return sides::bottom;
			}
			else if (onePos.y < 0 && onePos.y > twoPos.y || onePos.y > 0 && onePos.y > twoPos.y) {
				std::cout << "TOP" << std::endl;
				return sides::top;
			}
		}
		else {
			if (onePos.x < 0 && onePos.x < twoPos.x || onePos.x > 0 && onePos.x < twoPos.x) {
				std::cout << "LEFT" << std::endl;
				return sides::left;
			}
			else if (onePos.x < 0 && onePos.x > twoPos.x || onePos.x > 0 && onePos.x > twoPos.x) {
				std::cout << "RIGHT" << std::endl;
				return sides::right;
			}
		}
	}
	return sides::none;
}

void CollisionManager::MoveObject(Entity2D* player, Entity2D* object)
{
	float movement = 0.0f;
	sides cPosition = CheckOverlapCollisions(player, object);
	switch (cPosition) {
	case sides::none:
		break;
	case sides::top:
		//object->position = glm::vec3(object->position.x, object->position.y + speedPlayer, object->position.z);
		movement = (player->position.y + player->scalation.y) - (object->position.y - object->scalation.y);
		cout << player->position.y << endl;
		object->SetPosition(object->position.x, object->position.y - movement, object->position.z);
		//entity1->setPosition(entity1->transform.position.x, entity1->transform.position.y + speedEntity1, entity1->transform.position.z);
		break;
	case sides::right:
		object->position = glm::vec3(object->position.x + movement, object->position.y, object->position.z);
		//entity1->setPosition(entity1->transform.position.x + speedEntity1, entity1->transform.position.y, entity1->transform.position.z);
		break;
	case sides::bottom:
		object->position = glm::vec3(object->position.x, object->position.y - movement, object->position.z);
		//entity1->setPosition(entity1->transform.position.x, entity1->transform.position.y - speedEntity1, entity1->transform.position.z);
		break;
	case sides::left:
		object->position = glm::vec3(object->position.x - movement, object->position.y, object->position.z);
		//entity1->setPosition(entity1->transform.position.x - speedEntity1, entity1->transform.position.y, entity1->transform.position.z);
		break;
	default:
		break;
	}
}

float CollisionManager::GetOverlap(Entity2D* player, Entity2D* object)
{
	return 0.0f;
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


