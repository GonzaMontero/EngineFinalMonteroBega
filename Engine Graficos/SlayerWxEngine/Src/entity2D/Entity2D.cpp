#include "Entity2D.h"

Entity2D::Entity2D() : Entity()
{
	lastPosition = position;
}
#include <iostream>
bool Entity2D::CheckCollisionAABB(Entity2D& vs)
{
	if (canCollision &&  vs.canCollision)
	{

		if  (position.x - localScale.x / 2 < vs.position.x + vs.localScale.x / 2 &&
			 position.x + localScale.x / 2 > vs.position.x - vs.localScale.x / 2 &&
			 position.y - localScale.y / 2 < vs.position.y + vs.localScale.y / 2 &&
			 position.y + localScale.y / 2 > vs.position.y - vs.localScale.y / 2)
		{

			float deltaX = std::abs(position.x - vs.position.x);
			float deltaY = std::abs(position.y - vs.position.y);

			if (deltaX > deltaY) 
			{
				if (position.x < vs.position.x) 
				{
					//left vsRight
					deltaX = std::abs((vs.position.x - vs.localScale.x / 2) - (position.x + localScale.x / 2));
					CalculateAfterCollision(deltaX,glm::vec2(-1,0));
				}
				else 
				{
					//right vsLeft
					deltaX = std::abs((vs.position.x + vs.localScale.x / 2) - (position.x - localScale.x / 2));
					CalculateAfterCollision(deltaX, glm::vec2(1, 0));
				}
			}
			else
			{
				if (position.y < vs.position.y)
				{
					//up vsDown
					deltaY = std::abs((vs.position.y - vs.localScale.y/2)- (position.y + localScale.y / 2));
					CalculateAfterCollision(deltaY, glm::vec2(0, -1));
				}
				else 
				{
					//down vsUp
					deltaY = std::abs((vs.position.y + vs.localScale.y / 2) - (position.y - localScale.y / 2));
					CalculateAfterCollision(deltaY, glm::vec2(0, 1));
				}
			}
			
			return true;
		}
	}
	return false;
}

float Entity2D::GetScaleX()
{
	return localScale.x;
}

float Entity2D::GetScaleY()
{
	return localScale.y;
}
void Entity2D::BackToLastPosition()
{
	position = lastPosition;
}
void Entity2D::CalculateAfterCollision(float distance, glm::vec2 axis)
{
	distance = glm::abs(distance);
	SetPosition(GetPositionX() + (axis.x * distance),GetPositionY() + (axis.y * distance), GetPositionZ());
}