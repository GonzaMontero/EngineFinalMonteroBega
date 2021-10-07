#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Export.h"

class ENGINE_API Camera {
public:
	Camera();
	~Camera();
	void Init();

	glm::mat4 proj;
	glm::mat4 view;

	unsigned int projIndex;
	unsigned int viewIndex;
};

#endif // !CAMERA_H

