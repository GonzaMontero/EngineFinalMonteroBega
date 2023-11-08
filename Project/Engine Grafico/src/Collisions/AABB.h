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
	public:
		AABB();
		AABB(glm::vec3& min, glm::vec3& max);
		AABB(glm::vec3& inCenter, float iI, float iJ, float iK);
		~AABB();
		bool IsOnFrustum(Frustrum& camFrustum, Entity2D* mesh);
		bool IsOnOrForwardPlan(Plane& plane);
		glm::vec3 GetCenter();
		glm::vec3 GetExtents();
	};
}

#endif
