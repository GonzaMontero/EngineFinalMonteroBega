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
	testSprite->SetScale(130, 130, -1);
	testSprite->SetPosition(300, 300, -1);

	testSprite2 = new Sprite(false, "res/JPGExample.jpg", &render);
	testSprite2->Init();
	testSprite2->SetScale(50, 50, -1);
	testSprite2->SetPosition(250, 100, -1);
	valorTranslateX = 250;
	valorTranslateY = 100;

	spriteSheet = new Sprite(true, "res/link_sprite_sheet.png", &render);
	spriteSheet->Init();
	spriteSheet->SetScale(80, 80, -1);
	spriteSheet->SetPosition(250, 100, -1);

	testSprite->SetTrigger(true);


	// 961  832

	playerAnim[0] = new Animation();
	playerAnim[0]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 10, 10, 0);

	playerAnim[1] = new Animation();
	playerAnim[1]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 10, 10, 1);

	playerAnim[2] = new Animation();
	playerAnim[2]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 10, 10, 2);

	playerAnim[3] = new Animation();
	playerAnim[3]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 10, 10, 3);

	playerAnim[4] = new Animation();
	playerAnim[4]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 3, 3, 4);

	playerAnim[5] = new Animation();
	playerAnim[5]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 1, 1, 5);

	playerAnim[6] = new Animation();
	playerAnim[6]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 3, 3, 6);

	playerAnim[7] = new Animation();
	playerAnim[7]->addFrame(0, 0, 961 / 10, 832 / 8, 961, 832, 1.0, 3, 3, 7);


	spriteSheet->setAnimation(playerAnim[7]);
	spriteSheet->SetCurrentAnimationIndex(0);
	spriteSheet->SetRotation(0, 0, 0);
}
void Game::updateGame() {

	spriteSheet->updateAnimation(timer);

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

	if (input.GetKeyDown(KeyCode::S))
	{
		spriteSheet->setAnimation(playerAnim[3]);
	}
	if (input.GetKeyDown(KeyCode::W))
	{
		spriteSheet->setAnimation(playerAnim[1]);
	}
	if (input.GetKeyDown(KeyCode::A))
	{
		spriteSheet->setAnimation(playerAnim[0]);
	}
	if (input.GetKeyDown(KeyCode::D))
	{
		spriteSheet->setAnimation(playerAnim[2]);
	}

	if (input.GetKeyUp(KeyCode::S))
	{
		spriteSheet->setAnimation(playerAnim[7]);
	}
	if (input.GetKeyUp(KeyCode::W))
	{
		spriteSheet->setAnimation(playerAnim[5]);
	}
	if (input.GetKeyUp(KeyCode::A))
	{
		spriteSheet->setAnimation(playerAnim[4]);
	}
	if (input.GetKeyUp(KeyCode::D))
	{
		spriteSheet->setAnimation(playerAnim[6]);
	}


	spriteSheet->SetPosition(valorTranslateX, valorTranslateY, -1);

	if (collision->CheckAABBCollisions(spriteSheet, testSprite)) {
		if (testSprite->isTrigger) {
			cout << "Chocan" << endl;
			if (testSprite->freeze) {

			}
			else {
				cout << spriteSheet->position.y << endl;
				collision->MoveObject(spriteSheet, testSprite);
			}
		}
	}

	testSprite->DrawSprite();
	//testSprite2->DrawSprite();
	spriteSheet->DrawSprite();
}
void Game::unload() {

}