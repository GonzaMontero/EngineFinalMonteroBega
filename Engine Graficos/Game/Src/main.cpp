#include "game/Game.h"

int main(void)
{
	Game* myGame = new Game();
	myGame->Play();
	if(myGame != nullptr) delete myGame;
	return 0;
}