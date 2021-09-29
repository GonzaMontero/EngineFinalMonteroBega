#ifndef ENTITY_H
#define ENTITY_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Export.h"
#include "renderer.h"

class ENGINE_API Entity {
public:
	Renderer* renderer;

	glm::mat4 translate;
	glm::mat4 rotate;
	glm::mat4 scale;
	glm::mat4 model;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scalation;

	Entity(Renderer* _renderer);
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void Translate(float x, float y, float z);
	void UpdateModel();
};
#endif // !ENTITY_H