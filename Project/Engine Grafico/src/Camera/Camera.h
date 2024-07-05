#ifndef CAMERA_H
#define CAMERA_H

#include "../Utils/Export.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


namespace Engine {
	class Renderer;

	struct ENGINE_API CameraData
	{
		glm::vec3 _position;
		glm::vec3 _lookPositon;
		glm::vec3 _upVector;
	};

	class ENGINE_API Camera {
	public:
		Camera(Renderer* renderer, glm::vec3 position, glm::vec3 lookPositon, glm::vec3 upVector);
		~Camera();

		void SetCameraTransform(glm::vec3 newPositon, glm::vec3 newLookPosition, glm::vec3 newUpVector);
		void MoveCamera(glm::vec3 newPosition);

	private:
		glm::mat4 _viewMatrix;
		glm::mat4 _projectionMatrix;
		CameraData _data;
		Renderer* _renderer;
	};
}
#endif // !CAMERA_H

