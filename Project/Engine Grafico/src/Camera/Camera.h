#ifndef CAMERA_H
#define CAMERA_H

#include "../Utils/Export.h"
#include "../Renderer/renderer.h"
#include "../Shader/Shader.h"
#include "../Entity/Entity2D.h"
#include "../Input/Input.h"
#include "../Utils/TimeManager.h"
#include "../Plane/Plane.h"

using namespace std;


namespace Engine {
	enum class ENGINE_API ProjectionType {
		orthographic, perspective
	};

	enum class ENGINE_API CamMode {
		firstPerson, thirdPerson
	};

	struct Frustrum {
		Plane topFace;
		Plane bottomFace;
		Plane rightFace;
		Plane leftFace;
		Plane farFace;
		Plane nearFace;
	};

	class ENGINE_API Camera:public Entity2D {
	private:
		Renderer* _renderer;
		ProjectionType _type;
		CamMode _mode;
		glm::mat4 _view;
		glm::mat4 _projection;
		Input inputCam;
		Time time;

		glm::vec3 _cameraPos;
		glm::vec3 _cameraFront;
		glm::vec3 _cameraUp;
		glm::vec3 _cameraRight;
		Frustrum _frustum;

		float _roll;
		float _yaw;
		float _pitch;
		bool _firstMouse;
		float _rotationAngle;
		glm::vec3 _worldUp;
	public:
		Camera(Renderer* renderer, ProjectionType type, CamMode mode);
		~Camera();

		void SetView(glm::vec3 direction, glm::vec3 up);
		void SetProjection(ProjectionType type);

		void Init(Shader& shader, GLFWwindow* window);

		void SetLookAt();

		void SetCameraMode(CamMode mode);
		void SetLookAt(glm::vec3 forward);
		void FollowTarget(glm::vec3 positionTarget);
		void RotateAroundTarget(float x, float z);

		void SetCameraFront(glm::vec3 cameraFront);
		void SetCameraUp(glm::vec3 cameraUp);
		glm::vec3 GetCameraFront();
		glm::vec3 GetCameraUp();

		void RotateCamera();

		glm::mat4 GetView();
		glm::mat4 GetProjection();
		glm::mat4 GetMVP();

		void SetYaw(float yaw);
		void SetPitch(float pitch);
		float GetYaw();
		float GetPitch();
		void RotateYaw(float yaw);
		void RotatePitch(float pitch);

		void UpdateRotation();

		ProjectionType GetProjectionType();
		Frustrum CreateFrustumFromCamera(float aspect, float fovY, float zNear, float zFar);
		CamMode GetCameraMode();

		Plane GetNear();
		Plane GetLeft();
		Plane GetRight();
		Plane GetFar();

		void Draw(Shader& shader);
	};
}
#endif // !CAMERA_H

