#include "Camera.h"


Camera::Camera() {

}
Camera::~Camera() {

}

void Camera::Init() {
	proj = glm::mat4(1.0);
	//proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.001f, 500.0f);
	view = glm::mat4(1.0);
}
