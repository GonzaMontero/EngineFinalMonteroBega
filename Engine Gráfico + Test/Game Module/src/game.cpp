#include "game.h"
Game::Game() {
	//testShape = new Shape(&render);

}
Game::~Game() {
}
void Game::init() {
	//testShape->Init(WHITE);
	//testShape->SetPosition(0, 0 ,0);
	valorRotacion = 0;
	valorTranslateX = 0;
	valorTranslateY = 0;
	valorEscala = 1;
	testSprite = new Sprite(true, "res/meme2.png", &render);
	testSprite->Init();
	testSprite->SetScale(80, 80, -1);
	testSprite->SetPosition(300, 300, -1);

	testSprite2 = new Sprite(false, "res/JPGExample.jpg", &render);
	testSprite2->Init();
	testSprite2->SetScale(50, 50, -1);
	testSprite2->SetPosition(250, 100, -1);
	valorTranslateX = 250;
	valorTranslateY = 100;
}
void Game::updateGame() {

	testSprite->DrawSprite();
	testSprite2->DrawSprite();
	testSprite2->SetPosition(valorTranslateX, valorTranslateY, -1);
	cout << "x:" << testSprite2->position.x << " y:" << testSprite2->position.y << " z:" << testSprite2->position.z << endl;
	//testShape->SetRotation(0, 0, valorRotacion);
	//testShape->SetPosition(valorTranslateX, valorTranslateY, 1);
	//testShape->SetScale(valorEscala, valorEscala, valorEscala);
    //testShape->Draw();
	if(input.GetKey(KeyCode::M))
	{
	//	testShape->EpilepsyMode();
	}
	if (input.GetKey(KeyCode::Q))
	{
		valorRotacion += 1;
	}
	if (input.GetKey(KeyCode::E))
	{
		valorRotacion -= 1;
	}
	if (input.GetKey(KeyCode::D))
	{
		valorTranslateX += 1;
	}
	if (input.GetKey(KeyCode::A))
	{
		valorTranslateX -= 1;
	}

	if (input.GetKey(KeyCode::W))
	{
		valorTranslateY += 1;
	}
	if (input.GetKey(KeyCode::S))
	{
		valorTranslateY -= 1;
	}
	if (input.GetKey(KeyCode::Z))
	{
		valorEscala -= 1;
	}
	if (input.GetKey(KeyCode::X))
	{
		valorEscala += 1;
	}
	if (input.GetKey(KeyCode::R))
	{
	//	testShape->UpdateColor(RED);
	}
	if (input.GetKey(KeyCode::G))
	{
	//	testShape->UpdateColor(GREEN);
	}
	if (input.GetKey(KeyCode::B))
	{
	//	testShape->UpdateColor(BLUE);
	}
	
}
void Game::unload() {

}