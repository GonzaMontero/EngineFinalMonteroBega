#include "Entity2D.h"
#include "../Collision/Collision Manager.h"
#include <math.h>
#include <algorithm>

using namespace Engine;

Entity2D::Entity2D() 
{
	_collisionManager = nullptr;
}

Entity2D::~Entity2D() 
{
	if (_collisionManager != NULL)
		_collisionManager->RemoveFromCollisionList(this);
}

void Engine::Entity2D::SetCollisionManager(CollisionManager* newCollisionManager)
{
	_collisionManager = newCollisionManager;
}

CollisionDirection Engine::Entity2D::CheckCollision(Entity2D& otherEntity, float& xOverlap, float& yOverlap)
{
	xOverlap = max(0.0f,
		min(GetTransform().position.x + fabs(GetTransform().scale.x) / 2.0f,
			otherEntity.GetTransform().position.x + fabs(otherEntity.GetTransform().scale.x) / 2.0f),
		max(GetTransform().position.x + fabs(GetTransform().scale.x) / 2.0f,
			otherEntity.GetTransform().position.x + fabs(otherEntity.GetTransform().scale.x) / 2.0f));

	yOverlap = max(0.0f,
		min(GetTransform().position.y + fabs(GetTransform().scale.y) / 2.0f,
			otherEntity.GetTransform().position.y + fabs(otherEntity.GetTransform().scale.y) / 2.0f),
		max(GetTransform().position.y + fabs(GetTransform().scale.y) / 2.0f,
			otherEntity.GetTransform().position.y + fabs(otherEntity.GetTransform().scale.y) / 2.0f));


	if (xOverlap != 0.0f && yOverlap != 0.0f)
	{
		if (xOverlap > yOverlap)
		{
			if (GetTransform().position.y < 0 && GetTransform().position.y < otherEntity.GetTransform().position.y ||
				GetTransform().position.y > 0 && GetTransform().position.y < otherEntity.GetTransform().position.y)
			{
				return CollisionDirection::UP;
			}
			else if (GetTransform().position.y < 0 && GetTransform().position.y > otherEntity.GetTransform().position.y ||
				GetTransform().position.y > 0 && GetTransform().position.y > otherEntity.GetTransform().position.y)
			{
				return CollisionDirection::DOWN;
			}
		}
		else
		{
			if (GetTransform().position.x < 0 && GetTransform().position.x < otherEntity.GetTransform().position.x ||
				GetTransform().position.x > 0 && GetTransform().position.x < otherEntity.GetTransform().position.x)
			{
				return CollisionDirection::RIGHT;
			}
			else if (GetTransform().position.x < 0 && GetTransform().position.x > otherEntity.GetTransform().position.x ||
				GetTransform().position.x > 0 && GetTransform().position.x > otherEntity.GetTransform().position.x)
			{
				return CollisionDirection::LEFT;
			}
		}
	}

	return CollisionDirection::NONE;
}

void Engine::Entity2D::ApplyCollisionRestriction(CollisionDirection direction, float& xOverlap, float& yOverlap, bool halfOverlap)
{
	float defYOverlap = halfOverlap ? yOverlap / 2 : yOverlap;
	float defXOverlap = halfOverlap ? xOverlap / 2 : xOverlap;

	switch (direction)
	{
	case Engine::CollisionDirection::UP:
		SetPos(GetTransform().position.x, GetTransform().position.y - defYOverlap, GetTransform().position.z);
		break;
	case Engine::CollisionDirection::DOWN:
		SetPos(GetTransform().position.x, GetTransform().position.y + defYOverlap, GetTransform().position.z);
		break;
	case Engine::CollisionDirection::LEFT:
		SetPos(GetTransform().position.x + defXOverlap, GetTransform().position.y, GetTransform().position.z);
		break;
	case Engine::CollisionDirection::RIGHT:
		SetPos(GetTransform().position.x - defYOverlap, GetTransform().position.y, GetTransform().position.z);
		break;
	case Engine::CollisionDirection::NONE:
	default:
		break;
	}
}