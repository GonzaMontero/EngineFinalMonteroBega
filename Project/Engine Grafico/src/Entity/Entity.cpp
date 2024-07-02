#include "Entity.h"
#include "../Renderer/renderer.h"

namespace Engine 
{
	Entity::Entity()
	{
		_renderer = NULL;
		
		//TRS Matrix Value Settings
		_model.trs = glm::mat4(1.0f);
		_model.translate = glm::mat4(1.0f);
		_model.rotation.x = glm::mat4(1.0f);
		_model.rotation.y = glm::mat4(1.0f);
		_model.rotation.z = glm::mat4(1.0f);
		_model.scale = glm::mat4(1.0f);

		//Transform Value Settings
		_transform.position = glm::vec3(0.0f);
		_transform.rotation = glm::vec3(0.0f);
		_transform.scale = glm::vec3(1.0f);

		UpdateModel();

		SetColor(glm::vec4(1.0f));
	}

	Entity::~Entity()
	{

	}

	void Entity::SetPos(glm::vec3 newPos)
	{
		_transform.position = newPos;
		_model.translate = glm::translate(glm::mat4(1.0f), newPos);
		UpdateModel();
	}

	void Entity::SetPos(float x, float y, float z)
	{
		SetPos(glm::vec3(x, y, z));
	}

	void Entity::SetRot(glm::vec3 newRot)
	{
		SetRotXAxis(newRot.x);
		SetRotYAxis(newRot.y);
		SetRotZAxis(newRot.z);
		UpdateModel();
	}

	void Entity::SetRot(float x, float y, float z)
	{
		SetRotXAxis(x);
		SetRotYAxis(y);
		SetRotZAxis(z);
		UpdateModel();
	}

	void Entity::SetScale(glm::vec3 newScal)
	{
		_transform.scale = newScal;

		_model.scale = glm::scale(glm::mat4(1.0f), _transform.scale);
		UpdateModel();
	}

	void Entity::SetScale(float x, float y, float z)
	{
		SetScale(glm::vec3(x, y, z));
	}

	void Entity::SetColor(glm::vec4 newColor)
	{
		_color = newColor;
	}

	void Entity::SetColor(float r, float g, float b, float a)
	{
		_color = glm::vec4(r, g, b, a);
	}

	void Entity::InvertX()
	{
		SetRotXAxis(-3.14169f);
		UpdateModel();
	}

	void Entity::InvertY()
	{
		SetRotYAxis(-3.14169f);
		UpdateModel();
	}

	void Entity::InvertZ()
	{
		SetRotZAxis(-3.14169f);
		UpdateModel();
	}

	glm::vec4 Entity::GetColor()
	{
		return _color;
	}

	Transform Entity::GetTransform()
	{
		return _transform;
	}

	void Entity::UpdateModel()
	{
		_model.trs = _model.translate * _model.rotation.x * _model.rotation.y * _model.rotation.z * _model.scale;
	}

	void Entity::SetRotXAxis(float x)
	{
		_transform.rotation.x = x;
		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		_model.rotation.x = glm::rotate(glm::mat4(1.0f), x, axis);
	}

	void Entity::SetRotYAxis(float y)
	{
		_transform.rotation.y = y;
		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		_model.rotation.x = glm::rotate(glm::mat4(1.0f), y, axis);
	}

	void Entity::SetRotZAxis(float z)
	{
		_transform.rotation.z = z;
		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		_model.rotation.x = glm::rotate(glm::mat4(1.0f), z, axis);
	}
}