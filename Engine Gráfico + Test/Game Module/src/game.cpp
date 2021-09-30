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
}
void Game::updateGame() {
	testShape->SetRotation(0, 0, valorRotacion);
	valorRotacion -= 0.01;
	testShape->Draw();
	if(input.GetKey(KeyCode::E))
	{
		testShape->EpilepsyMode();
	}
}
void Game::unload() {

}