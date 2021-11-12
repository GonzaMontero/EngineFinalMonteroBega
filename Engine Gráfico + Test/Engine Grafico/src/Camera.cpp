#include "Camera.h"


Camera::Camera() {
	proj = glm::mat4(1.0);
	view = glm::mat4(1.0);
	//proj = glm::ortho();
	//view = glm::lookAt();
}
Camera::~Camera() {

}


