#include "game.h"
Game::Game() {
	map = new Tilemap();
	testShape = new Shape(&render);
}
Game::~Game() {
}
void Game::init() {
	map->LoadTileMap("../res/Tilemaps/TilesPokemonTest.tmx");
	testShape->Init(RED, QUAD);
	testShape->SetScale(50, 50, 1);
	testShape->SetPosition(120, 110 ,0);
	valorRotacion = 0;
	valorEscala = 1;

	//testSprite = new Sprite(true, "res/meme2.png", &render);
	//testSprite->Init();
	//testSprite->SetScale(130, 130, -1);
	//testSprite->SetPosition(300, 300, -1);
	//testSprite->SetTrigger(true);
	//testSprite->SetFreeze(false);

	//testSprite2 = new Sprite(false, "res/JPGExample.jpg", &render);
	//testSprite2->Init();
	//testSprite2->SetScale(50, 50, -1);
	//testSprite2->SetPosition(250, 100, -1);
	//testSprite2->SetTrigger(true);
	//testSprite2->SetFreeze(true);

	//spriteSheet = new Sprite(true, "res/link_sprite_sheet.png", &render);
	//spriteSheet->Init();
	//spriteSheet->SetScale(80, 80, -1);
	//spriteSheet->SetPosition(50, 100, -1);


	playerSpeed = 100;

	// 961  832

	//playerAnim[0] = new Animation();
	//playerAnim[0]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 10, 10, 0);
	//
	//playerAnim[1] = new Animation();
	//playerAnim[1]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 10, 10, 1);
	//
	//playerAnim[2] = new Animation();
	//playerAnim[2]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 10, 10, 2);
	//
	//playerAnim[3] = new Animation();
	//playerAnim[3]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 10, 10, 3);
	//
	//playerAnim[4] = new Animation();
	//playerAnim[4]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 3, 3, 4);
	//
	//playerAnim[5] = new Animation();
	//playerAnim[5]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 1, 1, 5);
	//
	//playerAnim[6] = new Animation();
	//playerAnim[6]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 3, 3, 6);
	//
	//playerAnim[7] = new Animation();
	//playerAnim[7]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 3, 3, 7);
	//
	//
	//spriteSheet->setAnimation(playerAnim[7]);
	//spriteSheet->SetCurrentAnimationIndex(0);
	//spriteSheet->SetRotation(0, 0, 0);
}
void Game::updateGame() {

	//spriteSheet->updateAnimation(timer);

	if (input.GetKey(KeyCode::D))
	{
		//spriteSheet->SetPosition(spriteSheet->position.x + (playerSpeed * timer.GetDeltaTime()), spriteSheet->position.y, -1);
	}
	if (input.GetKey(KeyCode::A))
	{
		//spriteSheet->SetPosition(spriteSheet->position.x - (playerSpeed*timer.GetDeltaTime()), spriteSheet->position.y, -1);
	}

	if (input.GetKey(KeyCode::W))
	{
		//spriteSheet->SetPosition(spriteSheet->position.x, spriteSheet->position.y + (playerSpeed * timer.GetDeltaTime()), -1);
	}
	if (input.GetKey(KeyCode::S))
	{
		//spriteSheet->SetPosition(spriteSheet->position.x, spriteSheet->position.y - (playerSpeed * timer.GetDeltaTime()), -1);
	}

	if (input.GetKeyDown(KeyCode::S))
	{
		//spriteSheet->setAnimation(playerAnim[3]);
	}
	if (input.GetKeyDown(KeyCode::W))
	{
		//spriteSheet->setAnimation(playerAnim[1]);
	}
	if (input.GetKeyDown(KeyCode::A))
	{
		//->setAnimation(playerAnim[0]);
	}
	if (input.GetKeyDown(KeyCode::D))
	{
		//spriteSheet->setAnimation(playerAnim[2]);
	}

	if (input.GetKeyUp(KeyCode::S))
	{
		//spriteSheet->setAnimation(playerAnim[7]);
	}
	if (input.GetKeyUp(KeyCode::W))
	{
		//spriteSheet->setAnimation(playerAnim[7]);
	}
	if (input.GetKeyUp(KeyCode::A))
	{
		//spriteSheet->setAnimation(playerAnim[4]);
	}
	if (input.GetKeyUp(KeyCode::D))
	{
		//spriteSheet->setAnimation(playerAnim[6]);
	}	

	//collision->CheckAABBCollisions(spriteSheet, testSprite, playerSpeed * timer.GetDeltaTime());
	//collision->CheckAABBCollisions(spriteSheet, testSprite2, playerSpeed * timer.GetDeltaTime());

	//testSprite->DrawSprite();
	//testSprite2->DrawSprite();
	//spriteSheet->DrawSprite();
	testShape->Draw(QUAD);
}
void Game::unload() {
}