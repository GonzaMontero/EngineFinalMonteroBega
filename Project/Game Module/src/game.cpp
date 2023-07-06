#include "Game.h"

float speed = 100.f;

Game::Game() {

}

Game::~Game() {
	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
}

void Game::InitGame() {
	_shape = new Shape(Type::quad, GetRenderer(), basicShader);

	_shape->Init();

	_shape->Color(1.0f, 0.0f, 0.0f);
	_shape->transform.position = glm::vec3(0, 0, -30.0f);
	_shape->transform.scale = glm::vec3(10.0f, 10.0f, 1.0f);

	_shape->RotateX(1.0f * speed * time.GetDeltaTime());
}

void Game::PlayerInputs() {
	if (input.GetKey(KeyCode::W)) {
		_shape->transform.position.y += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::S)) {
		_shape->transform.position.y -= speed * time.GetDeltaTime();
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

	_shape->Draw();
}

void Game::UnloadGame() {

	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}
}