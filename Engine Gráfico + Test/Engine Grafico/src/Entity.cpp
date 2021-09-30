#include "Entity.h"

Entity::Entity(Renderer* _renderer)
{
	renderer = _renderer;

	translate = glm::mat4(1.0);
	scale = glm::mat4(1.0);
	rotateX = glm::mat4(1.0);
	rotateY = glm::mat4(1.0);
	rotateZ = glm::mat4(1.0);
	model = glm::mat4(1.0);
}

void Entity::SetPosition(float x, float y, float z) { //Set position funciona tomando las coordenadas X,Y,Z (que van de -1 a 1) y te transporta el shape
	position.x = x;
	position.y = y;
	position.z = z;

	translate = glm::translate(glm::mat4(1.0f),position); //Actualiza la matriz de posicion con los datos nuevos
	UpdateModel(); //Modifica la TRS matrix (translate * rotation * scale)
}

void Entity::SetScale(float x, float y, float z) { //Set scale aumenta o disminuye el tamaño del sprite (desconozco los límites exactos, ya que sirve para escalar
	scalation.x = x;
	scalation.y = y;
	scalation.z = z;

	scale = glm::scale(glm::mat4(1.0f), scalation); //Actualiza la matriz de escala con los datos nuevos
	UpdateModel(); //Modifica la TRS matrix (translate * rotation * scale)
}

void Entity::SetRotation(float x, float y, float z) { //Actualiza cada rotación por separado, ya que causan errores distintos si se corren en simultaneo
	SetRotationX(x);
	SetRotationY(y);
	SetRotationZ(z);
}

void Entity::SetRotationX(float x) { //Set rotation (X en este caso, solo toma una variable X y actualiza las matrices acorde al valor de rotación que se le entrega
	glm::vec3 axis{ 0.0f, 0.0f, 0.0f };

	axis[0] = 1.0f;
	axis[1] = 0.0f;
	axis[2] = 0.0f;

	rotation.x = x;
	rotateX = glm::rotate(glm::mat4(1.0f), x, axis);
	UpdateModel();
}

void Entity::SetRotationY(float y) {
	glm::vec3 axis{ 0.0f, 0.0f, 0.0f };

	axis[0] = 0.0f;
	axis[1] = 1.0f;
	axis[2] = 0.0f;

	rotation.y = y;
	rotateY = glm::rotate(glm::mat4(1.0f), y, axis);
	UpdateModel();
}

void Entity::SetRotationZ(float z) {
	glm::vec3 axis{ 0.0f, 0.0f, 0.0f };

	axis[0] = 0.0f;
	axis[1] = 0.0f;
	axis[2] = 1.0f;

	rotation.z = z;
	rotateZ = glm::rotate(glm::mat4(1.0f), z, axis);
	UpdateModel();
}

void Entity::Translate(float x, float y, float z) //Mueve el shape en una direccion (en vez de transportar, lo mueve)
{
	position.x += x;
	position.y += y;
	position.z += z;

	translate = glm::translate(glm::mat4(1.0f), position);
	UpdateModel();
}

void Entity::UpdateModel()
{
	model = translate * rotateX * rotateY * rotateZ * scale;
}