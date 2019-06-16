#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "map.h"
#include "TextureManager.h"
#include "Pokemon.h"
#include "game.h"
#include <fstream>

const int ESC = 27;
Game *game = nullptr;

int main(int argc, char **argv) {
	const int fps = 60;
	const int frameDelay = 1000 / fps;

	game = new Game();
	game->init();

	while (game->running()) {

		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}