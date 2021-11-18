#include "Camera.h"


Camera::Camera() {
	//view = glm::mat4(1.0);
	//view = glm::translate(view, glm::vec3(0, 0, 0));
	//proj = glm::ortho(0.0f, 600.0f, 0.0f, 600.0f, 0.01f, 100.0f);
	proj = glm::perspective(glm::radians(45.0f), 600.0f/ 600.0f, 0.01f, 100.0f);
	view = glm::lookAt(glm::vec3(0,0,-1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}
Camera::~Camera() {

}


