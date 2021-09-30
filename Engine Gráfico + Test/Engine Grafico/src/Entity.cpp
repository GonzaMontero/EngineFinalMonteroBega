#include "Entity.h"

Entity::Entity(Renderer* _renderer)
{
	renderer = _renderer;

	translate = glm::mat4(1.0);
	scale = glm::mat4(1.0);
	rotateX = glm::mat4(1.0);
	rotateY = glm::mat4(1.0);
	rotateZ = glm::mat4(1.0);
	model = glm::mat4(1.0);
}

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
	SetRotationX(x);
	SetRotationY(y);
	SetRotationZ(z);
}

void Entity::SetRotationX(float x) {
	glm::vec3 axis{ 0.0f, 0.0f, 0.0f };

	axis[0] = 1.0f;
	axis[1] = 0.0f;
	axis[2] = 0.0f;

	rotation.x = x;
	rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	UpdateModel();
}

void Entity::SetRotationY(float y) {
	glm::vec3 axis{ 0.0f, 0.0f, 0.0f };

	axis[0] = 0.0f;
	axis[1] = 1.0f;
	axis[2] = 0.0f;

	rotation.y = y;
	rotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	UpdateModel();
}

void Entity::SetRotationZ(float z) {
	glm::vec3 axis{ 0.0f, 0.0f, 0.0f };

	axis[0] = 0.0f;
	axis[1] = 0.0f;
	axis[2] = 1.0f;

	rotation.z = z;
	rotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
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
	model = translate * rotateX * rotateY * rotateZ * scale;
}