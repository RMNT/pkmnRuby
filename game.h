#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>
#include "../pkmnRuby/Pokemon.h"
#include <fstream>
#include <vector>

extern const int DIM;

extern const int MAPH;
extern const int MAPL;
extern SDL_Event ev;

//SDL_Window* Game::window = nullptr;

class Game {
	bool isRunning;
	SDL_Window* window;
	void getName();
	static std::string userName;
	void saveResult();
	void loadUserFile();
	static void printResults();
	static std::vector <std::string> userNames;
	static std::vector <int> points;
public:
	Game();
	~Game();

	//static SDL_Window* window;
	static SDL_Event ev;

	void init();
	void handleEvents();
	void update();
	void render();
	void clean();

	static SDL_Renderer *renderer;

	Map_better* map;
	bool running();
};

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
	static void Draw(SDL_Rect src, SDL_Texture* tex, SDL_Rect dest);
};

#endif // !GAME_H
