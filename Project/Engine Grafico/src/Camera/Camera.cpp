#include "Camera.h"

#include "glew.h"
#include "glfw3.h"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
#include "mat4x4.hpp"

#include "../Renderer/renderer.h"

namespace Engine
{
	Camera::Camera(Renderer* renderer, glm::vec3 position, glm::vec3 lookPosition, glm::vec3 upVector)
	{
		_renderer = renderer;

		_projectionMatrix = glm::perspective(glm::radians(90.0f),
			(float)_renderer->GetWindow()->GetWidth() / (float)_renderer->GetWindow()->GetHeight(), 0.1f, 500.0f);

		_renderer->SetProjectionMatrix(_projectionMatrix);

		SetCameraTransform(position, lookPosition, upVector);
	}

	Camera::~Camera()
	{

	}

	void Camera::SetCameraTransform(glm::vec3 newPositon, glm::vec3 newLookPosition, glm::vec3 newUpVector)
	{
		_data._position = newPositon;
		_data._lookPositon = newLookPosition;
		_data._upVector = newUpVector;

		_viewMatrix = glm::lookAt(newPositon, newLookPosition, newUpVector);
	}

	void Camera::MoveCamera(glm::vec3 newPosition)
	{
		_data._position += newPosition;
		_data._lookPositon += newPosition;
		SetCameraTransform(_data._position, _data._lookPositon, _data._upVector);
	}
}