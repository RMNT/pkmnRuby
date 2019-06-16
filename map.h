#pragma once
#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <string>
#include "../pkmnRuby/Pokemon.h"

extern const int DIM;

extern const int MAPH;
extern const int MAPL;
extern SDL_Event ev;

class Grass {
	void deleteGrass();
public:
	int** evenBetterGrass = nullptr;
	char gr;
	Grass();
	~Grass();
};

class User {
private:
	int startX = 6, startY = 4;
	
	int xpos, ypos;

	static int pkmnCount;

	SDL_Texture* userTexture;
	SDL_Rect srcRect, destRect;

protected:
	char ch;
public:
	bool stepped = false;
	Torchic* chic;
	int prev_x, prev_y;
	int x, y;
	SDL_Event button_click;
	static void setPkmntCount();
	static int getPkmnCount();
	User();
	User(const char* textureSheet, int x, int y);
	~User();
	int whatIsX();
	int whatIsY();

	void update();
	void render();

	void move(int key, Grass* green);
	int* foundPkmn(int* pkmnFound);
	int foundPkmn();
};
class Map_better {
	SDL_Rect src, dest, p_src, p_dest, o_src, o_dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	SDL_Texture* battle_back;
	SDL_Texture* pkmn, *gr;
public:
	int map[10][14];
	SDL_Rect battle_field;
	void init();
	void render_battle();
	bool isGrass();
	User* player;
	Grass green;
	void battle(Pokemon* mysterious);
	void findpokemon();
	void battle();
	Map_better();
	~Map_better();

	void drawMap();
};

#endif // !MAP_H
