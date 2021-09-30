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
	valorTranslateX = 0;
	valorTranslateY = 0;
	valorEscala = 1;
}
void Game::updateGame() {
	testShape->SetRotation(0, 0, valorRotacion);
	testShape->SetPosition(valorTranslateX, valorTranslateY, 1);
	testShape->SetScale(valorEscala, valorEscala, valorEscala);
	testShape->Draw();
	if(input.GetKey(KeyCode::M))
	{
		testShape->EpilepsyMode();
	}
	if (input.GetKey(KeyCode::Q))
	{
		valorRotacion += 0.01;
	}
	if (input.GetKey(KeyCode::E))
	{
		valorRotacion -= 0.01;
	}
	if (input.GetKey(KeyCode::D))
	{
		valorTranslateX += 0.01;
	}
	if (input.GetKey(KeyCode::A))
	{
		valorTranslateX -= 0.01;
	}

	if (input.GetKey(KeyCode::W))
	{
		valorTranslateY += 0.01;
	}
	if (input.GetKey(KeyCode::S))
	{
		valorTranslateY -= 0.01;
	}
	if (input.GetKey(KeyCode::Z))
	{
		valorEscala -= 0.01;
	}
	if (input.GetKey(KeyCode::X))
	{
		valorEscala += 0.01;
	}
	if (input.GetKey(KeyCode::R))
	{
		testShape->UpdateColor(RED);
	}
	if (input.GetKey(KeyCode::G))
	{
		testShape->UpdateColor(GREEN);
	}
	if (input.GetKey(KeyCode::B))
	{
		testShape->UpdateColor(BLUE);
	}
	
}
void Game::unload() {

}