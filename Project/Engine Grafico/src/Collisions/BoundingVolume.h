#ifndef BOUNDING_VOLUME_H
#define BOUNDING_VOLUME_H

#include "../Utils/Export.h"
#include "../Camera/Camera.h"
#include "../Entity/Entity2D.h"
#include "../Plane/Plane.h"

using namespace std;

namespace Engine {
	class ENGINE_API BoundingVolume {
	private:
	public:
		BoundingVolume();
		~BoundingVolume();
		virtual bool IsOnFrustum(Frustrum& camFrustum, Entity2D* mesh) = 0;
		virtual bool IsOnOrForwardPlan(Plane& plane) = 0;
		bool IsOnFrustum(Frustrum& camFrustum);
	};
}

#endif
