#include "Entity.h"

Entity::Entity()
{
	renderer = renderer->GetStaticRenderer();

	model = glm::mat4(1.0f);
	rotateX = glm::mat4(1.0f);
	rotateY = glm::mat4(1.0f);
	rotateZ = glm::mat4(1.0f);
	scale = glm::mat4(1.0f);
	translate = glm::mat4(1.0f);

	SetPosition(0, 0, 0);
	Rotate(0, 0, 0);
	Scale(1, 1, 1);
}

void Entity::UpdateModel()
{
	model = translate * rotateX * rotateY * rotateZ * scale;
}

void Entity::RotateX(float x)
{
	rotation[0] = x;
	glm::vec3 axis = { 0.0f, 0.0f, 1.0f };
	axis[0] = 1.0f;
	axis[1] = 0.0f;
	axis[2] = 0.0f;

	rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	UpdateModel();
}

void Entity::RotateY(float y)
{
	rotation[1] = y;
	glm::vec3 axis = { 0.0f, 0.0f, 1.0f };
	axis[0] = 0.0f;
	axis[1] = 1.0f;
	axis[2] = 0.0f;

	rotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	UpdateModel();
}

void Entity::RotateZ(float z)
{
	rotation[2] = z;
	glm::vec3 axis = { 0.0f, 0.0f, 1.0f };
	axis[0] = 0.0f;
	axis[1] = 0.0f;
	axis[2] = 1.0f;

	rotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
	UpdateModel();
}

void Entity::SetPosition(float x, float y, float z)
{
	lastPosition = position;
	position[0] = x;
	position[1] = y;
	position[2] = z;

	translate = glm::translate(glm::mat4(1.0f), position);
	UpdateModel();
}

void Entity::Scale(float x, float y, float z)
{
	if (x <= 0.00f) x = 0.01f;
	if (y <= 0.00f) y = 0.01f;
	if (z <= 0.00f) z = 0.01f;
	localScale[0] = x;
	localScale[1] = y;
	localScale[2] = z;

	scale = glm::scale(glm::mat4(1.0f), localScale);
	UpdateModel();
}

void Entity::Rotate(float x, float y, float z)
{
	RotateX(x);
	RotateY(y);
	RotateZ(z);
}

void Entity::Translate(float x, float y, float z)
{
	position[0] += x;
	position[1] += y;
	position[2] += z;

	translate = glm::translate(glm::mat4(1.0f), position);
	UpdateModel();
}
float Entity::GetPositionX()
{
	return position.x;
}
float Entity::GetPositionY()
{
	return position.y;
}
float Entity::GetPositionZ()
{
	return position.z;
}
