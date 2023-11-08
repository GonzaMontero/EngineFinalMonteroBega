#include "BoundingVolume.h"

using namespace Engine;

BoundingVolume::BoundingVolume() {

}

BoundingVolume::~BoundingVolume() {

}

bool BoundingVolume::IsOnFrustum(Frustrum& camFrustum) {
	return (IsOnOrForwardPlan(camFrustum.leftFace) &&
		IsOnOrForwardPlan(camFrustum.rightFace) &&
		IsOnOrForwardPlan(camFrustum.topFace) &&
		IsOnOrForwardPlan(camFrustum.bottomFace) &&
		IsOnOrForwardPlan(camFrustum.nearFace) &&
		IsOnOrForwardPlan(camFrustum.farFace));
}