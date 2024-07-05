#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "../Utils/Export.h"
#include "../Tilemap/Tilemap.h"
#include <list>

using namespace std;

namespace Engine{

	class Entity2D;

	class ENGINE_API CollisionManager {
	public:
		CollisionManager();
		~CollisionManager();

		void AddToCollisionList(Entity2D* entityToAdd, bool isStatic);
		void RemoveFromCollisionList(Entity2D* entityToRemove);
		bool IsInCollisionList(Entity2D* entityToCheck);

		void UpdateCollisions();
		void UpdateCollisions(Engine::Tilemap* tilemap);

	private:
		std::list<Entity2D*> _dynamicCollisionList;
		std::list<Entity2D*> _staticCollisionList;
	};
}

#endif // !COLLISION_MANAGER_H