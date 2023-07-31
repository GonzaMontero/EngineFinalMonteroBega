#include "Camera.h"

#include "glew.h"
#include "glfw3.h"
#include "matrix_transform.hpp"
#include "type_ptr.hpp"
#include "mat4x4.hpp"

#include "../Renderer/renderer.h"

using namespace Engine;

Camera::Camera(Renderer* renderer, ProjectionType type) {
	//Crea la camara y establece su renderer y tipo de proyeccion
	_renderer = renderer;
	_type = type;

	_view = glm::mat4(1.0);
	_projection = glm::mat4(1.0);
}

Camera::~Camera() {

}

void Camera::SetView(glm::vec3 direction, glm::vec3 up) {
	//Setea a donde ve la camara seteando el frende y el up
	_view = glm::translate(_view, transform.position);
}

void Camera::SetProjection(ProjectionType type) {
	//Determina el tipo de proyeccion de la camara, usamos orthographic,
	// la diferencia es que perspective es afectada por la percepccion de distancia, mientras orthographic no toma eso en concideracion
	_type = type;

	switch (_type)
	{
	case ProjectionType::orthographic:
		_projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.01f, 100.0f);
		break;
	case ProjectionType::perspective:
		_projection = glm::perspective(glm::radians(45.0f), GLfloat(1280.0f) / GLfloat(720.0f), 0.01f, 100.0f);
		break;
	default:
		break;
	}
}

void Camera::Init(Shader& shader) {
	//Se setean las matrices MVP  de la camara
	unsigned int transformLoc = glGetUniformLocation(shader.GetID(), "model");
	unsigned int viewLoc = glGetUniformLocation(shader.GetID(), "view");
	unsigned int projLoc = glGetUniformLocation(shader.GetID(), "projection");

	shader.Use();

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(GetModel()));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(GetProjection()));
}

glm::mat4 Camera::GetView() {
	return _view;
}

glm::mat4 Camera::GetProjection() {
	return _projection;
}

glm::mat4 Engine::Camera::GetMVP() {
	return GetProjection() * GetView() * GetModel();
}

ProjectionType Camera::GetProjectionType() {
	return _type;
}

void Camera::Draw(Shader& shader) {
	_renderer->DrawCamera(shader, GetModel(), GetView());
}