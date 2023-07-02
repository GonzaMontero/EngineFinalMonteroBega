#include "game.h"

int main() {
	Game* game = new Game();

	if (game != NULL) {

		game->Execute();
		delete game;
		game = NULL;
	}
	return 0;
}