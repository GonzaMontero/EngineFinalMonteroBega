#include "game.h"

int main() {
	Game* game = new Game();

	game -> initEngine();
	game->init();

	if (game != NULL) {

		game->update();

		game->unload();

		delete game;
	}
	return 0;
}