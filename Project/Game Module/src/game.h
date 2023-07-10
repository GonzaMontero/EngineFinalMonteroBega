#ifndef GAME_H
#define GAME_H

#include "../../Engine Grafico/src/BaseGame/BaseGame.h"
#include <vector>

using namespace Engine;

class Vector2 {
	int x;
	int y;
};

class Game : public BaseGame {
private:
	float _time = 0;
	
	Vector2 shapePos;
	Shape* _shape = NULL;
	Shape* _shape2 = NULL;
	Light* _light[4] = { NULL, NULL, NULL, NULL };
	//Light* _point1 = NULL;
	//Light* _point2 = NULL;
	Light* _dirLight = NULL;
	Light* _spotLight = NULL;
	Sprite* _sprite = NULL;
	ModelImp* _model = NULL;
public:
	Game();
	~Game();
	void PlayerInputs();
	void InitGame() override;
	void UpdateGame() override;
	void UnloadGame() override;
}; 
#endif // !GAME_H