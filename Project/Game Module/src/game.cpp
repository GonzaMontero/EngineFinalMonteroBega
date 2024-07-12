#include "Game.h"

Game::Game()
{
	_samurai = nullptr;
	_camera = nullptr;
	_tilemap = nullptr;

	_samuraiBreathingAnimationID = 0;
	_samuraiGuardingAnimationID = 0;
	_samuraiSwingAnimationID = 0;

	t = 0;
}

Game::~Game()
{

}

void Game::Init()
{
	glm::vec3 camStartingPos = { 0, 50, 150 };
	glm::vec3 camLookPos = { 0, 50, 0 };
	glm::vec3 camUpVector = { 0, 1, 0 };

	_camera = new Engine::Camera(_renderer, camStartingPos, camLookPos, camUpVector);
	_tilemap = new Engine::Tilemap(_renderer);

	if (_tilemap->ImportTilemap("../Game Module/res/textures/Map1.tmx"))
	{
		std::cout << "Tilemap Loaded";
	}
	else
	{
		std::cout << "Tilemap Fail to Load";
	}
}

void Game::Update()
{

}

void Game::Draw()
{
	_tilemap->Draw();
	//_samurai->Draw();
}

void Game::DeInit()
{
	delete _camera;

	_samurai->Denitialize();
	delete _samurai;
}
