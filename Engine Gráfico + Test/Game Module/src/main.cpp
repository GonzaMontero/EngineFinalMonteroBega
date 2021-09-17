#include "game.h"

int main() {
	Game* game = new Game();
	if (game != NULL) {
		game->init();
		game->update();
		game->unload();
		delete game;
		game = NULL;
	}
	return 0;
}