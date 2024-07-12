#ifndef GAME_H
#define GAME_H

#include "../../Engine Grafico/src/BaseGame/BaseGame.h"
#include <vector>

class Game : public Engine::BaseGame {
public:
	Game();
	~Game();

	void Init() override;
	void Update() override;
	void Draw() override;
	void DeInit() override;

private:
	float t = 0;
	Engine::Sprite* _samurai;
	Engine::Camera* _camera;
	Engine::Tilemap* _tilemap;

	int _samuraiBreathingAnimationID;
	int _samuraiGuardingAnimationID;
	int _samuraiSwingAnimationID;

	float _moveSpeed = 50;
	float _cameraSpeed = 30;
}; 
#endif // !GAME_H