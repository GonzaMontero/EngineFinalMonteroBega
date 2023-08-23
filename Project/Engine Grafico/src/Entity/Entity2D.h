#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "../Utils/Export.h"
#include "mat4x4.hpp"
#include "vec3.hpp"
#include <vector>

using namespace std;

namespace Engine {
	struct ENGINE_API Rotation {
		glm::mat4 x;
		glm::mat4 y;
		glm::mat4 z;
	};

	struct ENGINE_API Transform {
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	};

	struct ENGINE_API Model {
		glm::mat4 translate;
		Rotation rotation;
		glm::mat4 scale;
		glm::mat4 trs;
	};

	class ENGINE_API Entity2D {
	private:
		bool _hasParent;
	protected:
		Model model;
		void UpdateMatrices();
		void UpdateModel();
		void UpdateForward();
		void UpdateUp();
		void UpdateRight();
	public:

#pragma region Methods and Attributes for Scene Graph

		std::vector<Entity2D*> children;
		Entity2D* _parent = nullptr;
		bool m_isDirty;

		void AddChild(Entity2D* entity);
		glm::mat4 GetLocalModelMatrix();
		void UpdateSelfAndChild();

		void ComputeModelMatrix();
		void ComputeModelMatrix(const glm::mat4& parentGlobalModelMatrix);
		void SetLocalPosition(const glm::vec3& newPosition);
		const glm::mat4& GetModelMatrix();
		bool IsDirty();
		void ForceUpdateSelfAndChild();

		inline void SetParent(Entity2D* parent);
		inline bool GetHasParent();
		void UpdateVectors();
#pragma endregion

#pragma region Methods and Attributes for standard use

		Transform transform;
		Entity2D();
		~Entity2D();
		void RotateX(float angle);
		void RotateY(float angle);
		void RotateZ(float angle);
		void Translate(float x, float y, float z);
		glm::vec2 Lerp(glm::vec2 a, glm::vec2 b, float t);
		void Scale(float x, float y, float z);
		glm::mat4 GetModel();

#pragma endregion
	};
}

#endif // !ENTITY2D_H
