#include "game.h"

int main() {
	Game* game = new Game();

	game->InitEngine(800, 600, "Engine Montero");

	delete game;
}