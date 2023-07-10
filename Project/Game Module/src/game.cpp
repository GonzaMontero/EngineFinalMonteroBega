#include "Game.h"

float speed = 100.f;

Game::Game() {

}

Game::~Game() {

	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}

	if (_shape2 != NULL) {
		delete _shape2;
		_shape2 = NULL;
	}

	if (_light != NULL) {
		delete _light;
		_light = NULL;
	}
}

void Game::InitGame() {

	_sprite = new Sprite(true, "res/textures/container2.png", GetRenderer(), basicShader);

	_shape = new Shape(Type::cube, GetRenderer(), basicShader);
	_shape2 = new Shape(Type::cube, GetRenderer(), basicShader);
	_light = new Light(GetRenderer(), basicShader);

	_shape->Init();
	_shape2->Init();

	_sprite->Init();

	_light->transform.position = glm::vec3(0.0f, 0.0f, 1.0f);
	_light->SetColor(1.0f, 1.0f, 0.0f);

	_shape->Color(1.0f, 0.0f, 0.0f);
	_shape->transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	_shape->transform.scale = glm::vec3(3.0f, 3.0f, 3.0f);

	_shape2->Color(0.0f, 0.0f, 1.0f);
	_shape2->transform.position = glm::vec3(2.0f, 0.0f, -10.0f);
	_shape2->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);

	_shape->RotateX(1.0f * speed * time.GetDeltaTime());

	_sprite->transform.position = glm::vec3(15.0f, 0.0f, -10.0f);
	_sprite->transform.scale = glm::vec3(5.0f, 5.0f, 5.0f);
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
	else if (input.GetKey(KeyCode::LEFT)) {
		_light->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::RIGHT)) {
		_light->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::UP)) {
		_light->transform.position.z -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::DOWN)) {
		_light->transform.position.z += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::T)) {
		float value = 10.0f;
		value += 20.0f * time.GetDeltaTime();
		_shape2->RotateZ(value);
	}
}

void Game::UpdateGame() {

	PlayerInputs();

	_camera->FollowTarget(_shape->transform.position);

	_shape->Draw();
	_shape2->Draw();
	_light->Draw();

	_sprite->DrawSprite();
}

void Game::UnloadGame() {

	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

	if (_shape != NULL) {
		delete _shape;
		_shape = NULL;
	}

	if (_shape2 != NULL) {
		delete _shape2;
		_shape2 = NULL;
	}

	if (_light != NULL) {
		delete _light;
		_light = NULL;
	}
}