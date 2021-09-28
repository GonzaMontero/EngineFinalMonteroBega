#include "Entity.h"

void Entity::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;

	translate;
}
void Entity::SetScale(float x, float y, float z) {
	scalation.x = x;
	scalation.y = y;
	scalation.z = z;
}
void Entity::SetRotation(float x, float y, float z) {
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}
void Entity::Translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
}