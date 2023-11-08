#ifndef PLANE_H
#define PLANE_H

#include "../Utils/Export.h"
#include "../Entity/Entity.h"
#include "glm.hpp"
#include "vec3.hpp"

#include <iostream>

using namespace std;

namespace Engine {
	class ENGINE_API Plane: public Entity {
	private:
		glm::vec3 _normal;
		float _distance;
	public:
		Plane();
		Plane(glm::vec3 normal, float distance);
		Plane(const glm::vec3& p1, const glm::vec3& normal);
		~Plane();
		void SetNormal(glm::vec3 normal);
		void SetDistance(float distance);
		//Plane(glm::vec3 normal, glm::vec3 point);
		Plane(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		glm::vec3 GetNormal();
		float GetDistance();
		float GetSignedDistanceToPlane(const glm::vec3& point);
		bool SameSide(glm::vec3 a, glm::vec3 b);
		void Set3Points(glm::vec3 a, glm::vec3 b, glm::vec3 c);
		void Flip();
		float GetDistanceToPoint(glm::vec3 point);
		bool GetSide(glm::vec3 point);
		bool SameSideA(glm::vec3 pointA, glm::vec3 pointB);
		//bool SameSide
	};
}

#endif
