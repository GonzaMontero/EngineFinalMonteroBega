#ifndef ENTITY2D_H
#define ENTITY2D_H
#include "export/export.h"
#include "entity/Entity.h"

class SlayerWxEngine_API Entity2D : public Entity
{
public:
	Entity2D();
	bool CheckCollisionAABB(Entity2D& vs);
	bool canCollision = false;
	float GetScaleX();
	float GetScaleY();
	void BackToLastPosition();
	void CalculateAfterCollision(float distance, glm::vec2 axis);
};

#endif
