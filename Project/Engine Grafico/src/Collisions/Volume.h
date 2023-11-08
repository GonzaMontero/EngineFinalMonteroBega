#ifndef VOLUME_H
#define VOLUME_H

#include "../Utils/Export.h"
#include "../Camera/Camera.h"
#include "../Entity/Entity2D.h"

namespace Engine {
	class ENGINE_API Volume {
	private:
	public:
		Volume();
		~Volume();
		virtual bool IsOnFrustum(const Frustrum& camFrustum, const Transform& modelTransform) = 0;
	};
}

#endif
