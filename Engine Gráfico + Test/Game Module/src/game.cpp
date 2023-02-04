#include "Game.h"

float speed = 100.f;

Game::Game() {

}

Game::~Game() {
	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

	if (_player != NULL) {
		delete _player;
		_player = NULL;
	}

	if (_map != NULL) {
		delete _map;
		_map = NULL;
	}
}

void Game::InitGame() {

	_sprite = new Engine::Sprite(true, "res/textures/samurai.png", GetRenderer(), textureShader);
	_player = new Animation();

	_map = new Tilemap(glm::ivec2(16, 16), "res/textures/FD_Free_Tiles.png", textureShader, GetRenderer());
	_map->SetTilesInfo("res/tilemap/Tiles.tsx");
	_map->LoadMap("res/tilemap/Map1.tmx");

	_sprite->Init();


	_player->Init(_sprite, glm::ivec2(6, 3));

	_player->AddAnimation(0, 6, false, 1.f);
	_player->AddAnimation(6, 11, false, 1.f);
	_player->AddAnimation(12, 14, true, .4f);
	_player->SetAnimation(2);


	_sprite->Scale(50.0f, 50.0f, 1.0f);

	_sprite->Color(1.0f, 1.0f, 1.0f);
	_sprite->transform.position = glm::vec3(300, 300, 1);
}

void Game::PlayerInputs() {
	if (input.GetKey(KeyCode::W)) {
		_sprite->transform.position.y += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::S)) {
		_sprite->transform.position.y -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::D)) {
		_sprite->transform.position.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::A)) {
		_sprite->transform.position.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::X)) {
		_sprite->transform.scale.x -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::C)) {
		_sprite->transform.scale.x += speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::Y)) {
		_sprite->transform.scale.y -= speed * time.GetDeltaTime();
	}
	else if (input.GetKey(KeyCode::U)) {
		_sprite->transform.scale.y += speed * time.GetDeltaTime();
	}

	if (input.GetMouseButton(MouseButtons::LEFT_MOUSE_BUTTON)) {
		_player->SetAnimation(0);
	}
	if (input.GetMouseButton(MouseButtons::RIGHT_MOUSE_BUTTON)) {
		_player->SetAnimation(1);
	}
}
void Game::UpdateGame() {

	PlayerInputs();

	if (!_player->GetCurrentAnimation().loop && _player->GetCurrentAnimation().hasEnded) {
		_player->SetAnimation(2);
	}

	_map->Draw();

	_map->CheckCollisionWithTileMap(_sprite, _sprite->transform.position, speed * time.GetDeltaTime());

	_player->UpdateIndex(time);

	_sprite->DrawAnimation(_player->GetUVs(_player->GetCurrentIndex()));

}

void Game::UnloadGame() {

	if (_sprite != NULL) {
		delete _sprite;
		_sprite = NULL;
	}

	if (_player != NULL) {
		delete _player;
		_player = NULL;
	}

	if (_map != NULL) {
		delete _map;
		_map = NULL;
	}
}