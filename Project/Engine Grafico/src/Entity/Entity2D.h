#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "../Utils/Export.h"
#include "Entity.h"

namespace Engine {

	class CollisionManager;
	enum class CollisionDirection {UP, DOWN, LEFT, RIGHT, NONE};

	class ENGINE_API Entity2D : Entity
	{
	public:
		Entity2D();
		~Entity2D();
		
		//Sets manager which will control the reactions to collisions and the directions in which they are moving
		void SetCollisionManager(CollisionManager* newCollisionManager);

		//Check if objects are colliding + move and check collision direction
		CollisionDirection CheckCollision(Entity2D& otherEntity, float& xOverlap, float& yOverlap);
		void ApplyCollisionRestriction(CollisionDirection direction, float& xOverlap, float& yOverlap, bool halfOverlap);
	private:
		CollisionManager* _collisionManager;
	};
}

#endif // !ENTITY2D_H
