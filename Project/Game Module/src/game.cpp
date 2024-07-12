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

	if (_tilemap->ImportTilemap("../Game Module/res/textures/Map3.tmx"))
	{
		std::cout << "Tilemap Loaded";
	}
	else
	{
		std::cout << "Tilemap Fail to Load";
	}

	_samurai = new Engine::Sprite(_renderer, "../Game Module/res/textures/samurai.png", false);

	Engine::AtlasConfigurations _samuraiAnimationAtlasConfig;

	_samuraiAnimationAtlasConfig.CutByCount(6, 3, 2, 1, 2);
	_samuraiBreathingAnimationID = _samurai->CreateAnimation(_samuraiAnimationAtlasConfig);

	_samurai->SetAnimationFullTime(_samuraiBreathingAnimationID, .5f);

	_samurai->SetScale(32, 32, 1);
	_samurai->SetPos(-80, 20, 0);

	ChangeClearColor(glm::vec4(0, 0, 0, 1));

	AttachCollider(_samurai, false);
}

void Game::Update()
{
	if (IsKeyPressed(ENGINE_KEY_LEFT))
	{
		glm::vec3 movement = { Engine::Time::GetDeltaTime() * -_cameraSpeed, 0, 0 };
		_camera->MoveCamera(movement);
	}
	else if (IsKeyPressed(ENGINE_KEY_RIGHT))
	{
		glm::vec3 movement = { Engine::Time::GetDeltaTime() * _cameraSpeed, 0, 0 };
		_camera->MoveCamera(movement);
	}
	if (IsKeyPressed(ENGINE_KEY_UP))
	{
		glm::vec3 movement = { 0, Engine::Time::GetDeltaTime() * _cameraSpeed , 0 };
		_camera->MoveCamera(movement);
	}
	else if (IsKeyPressed(ENGINE_KEY_DOWN))
	{
		glm::vec3 movement = { 0, Engine::Time::GetDeltaTime() * -_cameraSpeed , 0 };
		_camera->MoveCamera(movement);
	}
}

void Game::Draw()
{
	_tilemap->Draw();
	_samurai->Draw();
}

void Game::DeInit()
{
	delete _camera;

	_samurai->Denitialize();
	delete _samurai;
}
