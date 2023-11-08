#ifndef AABB_H
#define AABB_H

#include "../Utils/Export.h"

#include "glm.hpp"

#include "../Collisions/BoundingVolume.h"
#include "../Plane/Plane.h"
#include "../Entity/Entity2D.h"

namespace Engine {
	class ENGINE_API AABB : public BoundingVolume {
	private:
		glm::vec3 _center;
		glm::vec3 _extents;
		AABB* _globalAABB;
	public:
		AABB();
		AABB(glm::vec3& min, glm::vec3& max);
		AABB(glm::vec3& inCenter, float iI, float iJ, float iK);
		~AABB();
		bool IsOnFrustum(Frustrum& camFrustum, Entity2D* mesh);
		bool IsOnFrustum(Frustrum& camFrustum, glm::mat4 worldModel);
		bool IsOnBSP(std::vector<Plane*> planes, Entity2D* mesh);
		void GenerateGlobalAABB(Entity2D* mesh);
		AABB* GetGlobalAABB();
		AABB GetGlobalAABBWithMatrix(glm::mat4 matrix);
		bool IsOnOrForwardPlan(Plane& plane);
		bool IsOnOrForwardPlan(Plane* plane);
		bool IsOnOrForwardPlan(Plane plane);
		bool IsOnOrBackwardPlan(Plane* plane);
		glm::vec3 GetCenter();
		glm::vec3 GetExtents();
		glm::vec3 min;
		glm::vec3 max;
		void UpdateAABB(glm::vec3 min, glm::vec3 max);
	};
}

#endif
