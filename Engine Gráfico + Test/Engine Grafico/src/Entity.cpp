#include "Entity.h"

void Entity::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;

	translate = glm::translate(glm::mat4(1.0f),position);
	UpdateModel();
}
void Entity::SetScale(float x, float y, float z) {
	scalation.x = x;
	scalation.y = y;
	scalation.z = z;

	scale = glm::scale(glm::mat4(1.0f), scalation);
	UpdateModel();
}
void Entity::SetRotation(float x, float y, float z) {
	glm::vec3 axis{ 0.0f, 0.0f, 0.0f };

	axis[0] = 1.0f;
	axis[1] = 1.0f;
	axis[2] = 1.0f;

	rotation.x = x;
	rotation.y = y;
	rotation.z = z;

	rotate = glm::rotate(glm::mat4(1.0f), x, axis);
	rotate = glm::rotate(glm::mat4(1.0f), y, axis);
	rotate = glm::rotate(glm::mat4(1.0f), z, axis);
	UpdateModel();
}
void Entity::Translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;

	translate = glm::translate(glm::mat4(1.0f), position);
	UpdateModel();
}
void Entity::UpdateModel()
{
	model = translate * rotate * scale;
}