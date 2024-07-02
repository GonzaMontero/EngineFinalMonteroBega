#ifndef ENTITY_H
#define ENTITY_H

#include "../Utils/Export.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

namespace Engine
{
	class Renderer;

	struct ENGINE_API Rotation {
		glm::mat4 x;
		glm::mat4 y;
		glm::mat4 z;
	};

	struct ENGINE_API Transform {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};

	struct ENGINE_API Model {
		glm::mat4 translate;
		Rotation rotation;
		glm::mat4 scale;
		glm::mat4 trs;
	};

	class ENGINE_API Entity
	{
	public:
		Entity();
		~Entity();

		//Methods to set certain parameters, in a combination of vector values or float values
		void SetPos(glm::vec3 newPos);
		void SetPos(float x, float y, float z);
		void SetRot(glm::vec3 newRot);
		void SetRot(float x, float y, float z);
		void SetScale(glm::vec3 newScal);
		void SetScale(float x, float y, float z);
		void SetColor(glm::vec4 newColor);
		void SetColor(float r, float g, float b, float a);

		//Functions to modify the parameters
		void InvertX();
		void InvertY();
		void InvertZ();

		//Getter values
		glm::vec4 GetColor();
		Transform GetTransform();

		//Virtual function so classes that inherit can call specific actions to perform during the draw portion
		virtual void Draw() = 0;

	protected:
		Renderer* _renderer;

		Transform _transform;
		Model _model;

		glm::vec4 _color;

		unsigned int VAO, VBO, EBO, _vertices;

		void UpdateModel();

	private:
		void SetRotXAxis(float x);
		void SetRotYAxis(float y);
		void SetRotZAxis(float z);
	};
}

#endif // !ENTITY_H
