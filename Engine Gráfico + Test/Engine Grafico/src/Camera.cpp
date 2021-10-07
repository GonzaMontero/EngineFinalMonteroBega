#include "Camera.h"


Camera::Camera() {
	proj = glm::mat4(1.0);
	view = glm::mat4(1.0);
}
Camera::~Camera() {

}


