#include "game.h"
Game::Game() {
	testShape = new Shape(&render);
}
Game::~Game() {
}
void Game::init() {
	testShape->Init(WHITE);
	testShape->SetPosition(0, 0 ,0);
	valorRotacion = 0;
	number = 0;
}
void Game::updateGame() {
	testShape->SetRotation(0, 0, valorRotacion);
	valorRotacion -= 0.01;
	testShape->Draw();
	switch (number) {
	case 0:
		number++;
		testShape->UpdateColor(BLUE);
		break;
	case 1:
		number++;
		testShape->UpdateColor(RED);
		break;
	case 2:
		number = 0;
		testShape->UpdateColor(GREEN);
		break;
	}
}
void Game::unload() {

}