#include "Game.h"

float speed = 100.f;

Game::Game() {

}

Game::~Game() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}

	if (_shape2 != NULL) {
		delete _shape2;
		_shape2 = NULL;
	}
}

void Game::InitGame() {
	_shape = new Shape(Type::quad, GetRenderer(), basicShader);
	_shape2 = new Shape(Type::quad, GetRenderer(), basicShader);

	_shape->Init();
	_shape2->Init();

	_shape->Color(1.0f, 0.0f, 0.0f);
	_shape->transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	_shape->transform.scale = glm::vec3(10.0f, 10.0f, 1.0f);

	_shape2->Color(0.0f, 0.0f, 1.0f);
	_shape2->transform.position = glm::vec3(2.0f, 0.0f, -10.0f);
	_shape2->transform.scale = glm::vec3(10.0f, 10.0f, 1.0f);

	_shape->RotateX(1.0f * speed * time.GetDeltaTime());
}

void Game::PlayerInputs() {

	if (input.GetKey(KeyCode::W)) {
		_shape->transform.position.z -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::S)) {
		_shape->transform.position.z += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::D)) {
		_shape->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::A)) {
		_shape->transform.position.x -= speed * time.GetDeltaTime();
	}
}

void Game::UpdateGame() {

	PlayerInputs();

	_camera->FollowTarget(_shape->transform.position);

	_shape->Draw();
	_shape2->Draw();
}

void Game::UnloadGame() {

	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}

	if (_shape2 != NULL) {
		delete _shape2;
		_shape2 = NULL;
	}
}