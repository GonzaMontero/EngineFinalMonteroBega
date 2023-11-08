#ifndef GAME_H
#define GAME_H

#include "../../Engine Grafico/src/BaseGame/BaseGame.h"
#include <string>
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
	Light* _dirLight = NULL;
	Light* _spotLight = NULL;

	Sprite* _sprite = NULL;
	ModelInstance* _model = NULL;
	Node* _modelLeft = NULL;
	Node* _modelRight = NULL;
	Node* _modelForward = NULL;
	//Node* _modelMobile = NULL;
	Node* _bspPlanes[3] = { NULL, NULL, NULL };
	BSPAlgorithm* _bsp = NULL;
	Frustrum camFrustum;
	//Plane _planes[3];

public:

	Game();
	~Game();

	void PlayerInputs();

	void HandleThirdPersonModelMovement();
	void HandleThirdPersonCameraMovement();
	void HandleFirstPersonCameraMovement();
	void HandleLightState();
	void HandleCamModeSwap();

	void InitGame() override;
	void UpdateGame() override;
	void UnloadGame() override;
};
#endif // !GAME_H