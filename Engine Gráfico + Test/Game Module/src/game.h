#ifndef GAME_H
#define GAME_H

#include "../../Engine Grafico/src/BaseGame/BaseGame.h"
#include <vector>

using namespace Engine;

class Game : public BaseGame {
private:
	float _time = 0;
	glm::vec2 shapePos = glm::vec2(0, 0);
	Sprite* _sprite = NULL;
	Animation* _player = NULL;
	Tilemap* _map = NULL;
public:
	Game();
	~Game();
	void PlayerInputs();
	void InitGame() override;
	void UpdateGame() override;
	void UnloadGame() override;
}; 
#endif // !GAME_H