#ifndef ENTITY_H
#define ENTITY_H
#include "export/export.h"
#include "renderer/renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class SlayerWxEngine_API Entity 
{
protected:
	glm::mat4 model;
	glm::mat4 translate;
	glm::mat4 rotateX;
	glm::mat4 rotateY;
	glm::mat4 rotateZ;
	glm::mat4 scale;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 localScale;
	glm::vec3 lastPosition;
	void UpdateModel();

	void RotateX(float x);
	void RotateY(float y);
	void RotateZ(float z);
public:
	Renderer* renderer;
	Entity();
	float weight = 0;
	float strength = 0;

	void SetPosition(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Translate(float x, float y, float z);
	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();
};

#endif
