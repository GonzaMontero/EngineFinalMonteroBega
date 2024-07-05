#include "Collision Manager.h"

namespace Engine {
	CollisionManager::CollisionManager()
	{

	}

	CollisionManager::~CollisionManager()
	{

	}

	void CollisionManager::AddToCollisionList(Entity2D* entityToAdd, bool isStatic)
	{
		entityToAdd->SetCollisionManager(this);
		isStatic ? _staticCollisionList.push_back(entityToAdd) : _dynamicCollisionList.push_back(entityToAdd);
	}

	void CollisionManager::RemoveFromCollisionList(Entity2D* entityToRemove)
	{
		_staticCollisionList.remove(entityToRemove);
		_dynamicCollisionList.remove(entityToRemove);
	}

	bool CollisionManager::IsInCollisionList(Entity2D* entityToCheck)
	{
		for (auto const& d1 : _dynamicCollisionList)
			if (d1 == entityToCheck) return true;

		for (auto const& s1 : _staticCollisionList)
			if (s1 == entityToCheck)return true;

		return false;
	}

	void CollisionManager::UpdateCollisions()
	{
		for (auto const& d1 : _dynamicCollisionList)
		{
			for (auto const& d2 : _dynamicCollisionList)
			{
				if (d1 != d2)
				{
					float overlapX = 0;
					float overlapY = 0;

					CollisionDirection currentCollision = d1->CheckCollision(*d2, overlapX, overlapY);

					if (currentCollision != CollisionDirection::NONE)
					{
						d1->ApplyCollisionRestriction(currentCollision, overlapX, overlapY, true);
						d2->ApplyCollisionRestriction(currentCollision, -overlapX, -overlapY, true);
					}
				}
			}
		}

		for (auto const& d : _dynamicCollisionList)
		{
			for (auto const& s : _staticCollisionList)
			{
				float overlapX = 0;
				float overlapY = 0;

				CollisionDirection currentColision = d->CheckCollision(*s, overlapX, overlapY);

				if (currentColision != CollisionDirection::NONE)
					d->ApplyCollisionRestriction(currentColision, overlapX, overlapY, false);
			}
		}
	}

	void CollisionManager::UpdateCollisions(Engine::Tilemap* tilemap)
	{
		for (auto const& d1 : _dynamicCollisionList)
		{
			for (auto const& d2 : _dynamicCollisionList)
			{
				if (d1 != d2)
				{
					tilemap->CheckCollision(*d1);
					tilemap->CheckCollision(*d2);

					float overlapX = 0;
					float overlapY = 0;

					CollisionDirection currentCollision = d1->CheckCollision(*d2, overlapX, overlapY);

					if (currentCollision != CollisionDirection::NONE)
					{
						d1->ApplyCollisionRestriction(currentCollision, overlapX, overlapY, true);
						d2->ApplyCollisionRestriction(currentCollision, overlapX, overlapY, true);
					}
				}
				else
					tilemap->CheckCollision(*d1);
			}
		}
	}
}
