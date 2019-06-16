#include <iostream>
#include <vector>
#include "stdafx.h"
#include <SDL.h>
#include <cmath>
#include <ctime>
#include "map.h"
#include "game.h"
#include <string>
#include <SDL_image.h>
#include "../pkmnRuby/Pokemon.h"

#define FIRE 1
#define NORMAL 2

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77

const int MAPH = 10;
const int MAPL = 14;
const int DIM = 60;

SDL_Event ev_battle;

Grass::Grass() {
	int which = 0;
	evenBetterGrass = new int*[2];

	for (int i = 0; i < 2; ++i) {
		evenBetterGrass[i] = new int[MAPH*MAPL];
	}
	for (int j = 0; j < MAPH*MAPL; ++j) {
		evenBetterGrass[0][j] = -1;
		evenBetterGrass[1][j] = -1;
	}

	std::vector<int> whereToGrowY{ 0, 0, 0, 0,  1, 1, 1, 1,  2, 2, 2, 2, 2, 2, 2, 2,   3, 3, 3, 3,   4, 4,  6, 6, 6, 6,   7, 7, 7, 7, 7, 7, 7, 7, 7,  7,    8, 8, 8, 8, 8, 8, 8, 8, 8, 8,       9, 9, 9, 9,  9,  9,  9, 9 };
	std::vector<int> whereToGrowX{ 0, 1, 2, 3,  0, 1, 2, 3,  2, 3, 4, 7, 8, 9, 10, 11, 7, 8, 9, 10,  8, 9,  8, 9, 10,11 , 0, 1, 2, 3, 4, 7, 8, 9, 10, 11,   1, 2, 3, 7, 8, 9, 10, 11, 12, 13,   6, 7, 8, 9, 10, 11, 12, 13 };

	while ((size_t)which < whereToGrowX.size()) {
		evenBetterGrass[0][which] = whereToGrowY[which];
		evenBetterGrass[1][which] = whereToGrowX[which];
		++which;
	}
}
Grass::~Grass() {
	deleteGrass();
}
void Grass::deleteGrass() {
	if (evenBetterGrass != nullptr) {
		for (int i = 0; i < 2; ++i) {
			delete[] evenBetterGrass[i];
		}
		delete[] evenBetterGrass;
		evenBetterGrass = nullptr;
	}
	else {
	}
}

User::User(const char* textureSheet, int x, int y) {
	userTexture = TextureManager::LoadTexture(textureSheet);

	xpos = x;
	ypos = y;

	pkmnCount = 0;

	chic = new Torchic();
}

void User::setPkmntCount() {
		++pkmnCount;
}

int User::getPkmnCount() {
	return pkmnCount;
}

User::User() {
}
User::~User() {
}
void User::update() {
	switch (Game::ev.type) {
	case SDL_KEYDOWN:
		switch (Game::ev.key.keysym.sym) {
			//case SDLK_LEFT:
		case SDLK_a:
			if (xpos - DIM > -1 * DIM) {
				xpos -= DIM;
			}
			break;
			//case SDLK_UP:
		case SDLK_w:
			if (ypos - DIM > -1 * DIM) {
				ypos -= 60;
			}
			break;
			//case SDLK_RIGHT:
		case SDLK_d:
			if (xpos + DIM < DIM * 14) {
				xpos += 60;
			}
			break;
			//case SDLK_DOWN:
		case SDLK_s:
			if (ypos + DIM < DIM * 10) {
				ypos += 60;
			}
		default:
			break;
		}
	default:
		break;
	}

	srcRect.h = DIM;
	srcRect.w = DIM;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = srcRect.h;
	destRect.w = srcRect.w;
	destRect.x = xpos;
	destRect.y = ypos;

}
void User::render() {
	SDL_RenderCopy(Game::renderer, userTexture, &srcRect, &destRect);
}
int User::whatIsX() {
	return xpos;
}
int User::whatIsY() {
	return ypos;
}
int User::pkmnCount;

Map_better::Map_better() : player() {
	dirt = TextureManager::LoadTexture("assets/dirt.png");
	grass = TextureManager::LoadTexture("assets/grass.png");
	water = TextureManager::LoadTexture("assets/water.png");
	battle_back = TextureManager::LoadTexture("assets/white.png");
	int which = 0;

	for (int i = 0; i < MAPH; ++i) {
		for (int j = 0; j < MAPL; ++j) {
			if ((i == green.evenBetterGrass[0][which]) && (j == green.evenBetterGrass[1][which])) {
				map[i][j] = 1;
				++which;
			}
			else {
				map[i][j] = 0;
			}
		}
	}

	src.y = src.x = dest.x = dest.y = 0;
	src.w = src.h = dest.h = dest.w = DIM;
}
void Map_better::init() {
	player = new User("assets/user.png", DIM * 6, DIM * 4);
}
Map_better::~Map_better() {
}
void Map_better::drawMap() {
	int type = 0;
	for (int i = 0; i < MAPH; ++i) {
		for (int j = 0; j < MAPL; ++j) {
			type = map[i][j];
			dest.x = j * DIM;
			dest.y = i * DIM;
			switch (type) {
			case 0:
				TextureManager::Draw(dirt, src, dest);
				break;
			case 1:
				TextureManager::Draw(grass, src, dest);
				break;
			case 3:
				TextureManager::Draw(water, src, dest);
				break;
			default:
				break;
			}
		}
	}
}
bool Map_better::isGrass() {
	int x = (this->player->whatIsX()) / DIM;
	int y = (this->player->whatIsY()) / DIM;

	if (this->map[y][x] == 1)
		return true;

	return false;
}
void Map_better::findpokemon() {
	double random = ((double)rand() / (RAND_MAX));
	if (random > 0.85) {
		Pokemon* mysterious;
		double mysteriousPkmn = ((double)rand()) / (RAND_MAX);
		if ((mysteriousPkmn < 0.5)) {
			mysterious = new Zigzagoon();
		}
		else {
			mysterious = new Wurmple();
		}
		pkmn = TextureManager::LoadTexture("assets/wurmple_back.png");
		gr = TextureManager::LoadTexture("assets/grass.png");
		battle(mysterious);
	}
}
void Map_better::battle(Pokemon* mysterious) {
	Pokemon* owners = player->chic;
	int start;
	int hp_battle = owners->hp;

	std::cout << "Rastas: " << mysterious->getName() << std::endl;
	std::cout << "Lygis: " << mysterious->level << std::endl << std::endl;
	std::cout << owners->getName() << " greitis: " << owners->get_spd() << std::endl;
	std::cout << mysterious->getName() << " greitis: " << mysterious->get_spd() << std::endl;

	if (owners->get_spd() < mysterious->get_spd()) {
		std::cout << "rastas greitesnis" << std::endl;
		start = 1;
	}
	else {
		std::cout << "playerio greitesnis arba abu lygus" << std::endl << std::endl;
		start = 0;
	}

	while ((hp_battle > 0) && (mysterious->hp > 0)) {
		int attac1 = (rand() % (7 - 2 + 1)) + 1;
		int attac2 = (rand() % (7 - 2 + 1)) + 1;

		std::cout << "rasto gyvybe: " << mysterious->hp << std::endl;
		std::cout << "playerio gyvybe: " << hp_battle << std::endl << std::endl;

		if (start) {
			mysterious->attack();
			std::cout << " -" << attac1 << std::endl;
			owners->attack();
			std::cout << " -" << attac2 << std::endl;
			std::cout << std::endl;
		}
		else {
			owners->attack();
			std::cout << " -" << attac2 << std::endl;
			mysterious->attack();
			std::cout << " -" << attac1 << std::endl;
			std::cout << std::endl;
		}
		mysterious->hp -= attac1;
		hp_battle -= attac2;
	}
	if (hp_battle > 0) {
		std::cout << "playeris laimejo" << std::endl;
		User::setPkmntCount();
	}
	else
		std::cout << "rastas laimejo" << std::endl;

	std::cout << "dabar turi: " << User::getPkmnCount() << " pokemonus" << std::endl;

	battle_field.h = 600;
	battle_field.w = 840;
	battle_field.x = 0;
	battle_field.y = 0;

	p_src.x = p_src.y = p_dest.x = p_dest.y = DIM;
	p_src.h = p_src.w = p_dest.h = p_dest.w = DIM * 6;

	o_src.x = o_src.y = o_dest.x = o_dest.y = 0;
	o_src.h = o_src.w = o_dest.h = o_dest.w = DIM * 6;

	//std::cout << "pkmn: " << mysterious->front << std::endl;

	char c;
	//check if texture is successfully created
	if (!pkmn)
		std::cout << "nesukure pokemona" << std::endl << std::endl;

	//for (int i = 0; i < 200; ++i) {
		SDL_RenderFillRect(Game::renderer, &battle_field);
		SDL_RenderPresent(Game::renderer);
		//for (int j = 0; j < 300; ++j) {
		TextureManager::Draw(pkmn, p_src, p_dest);
		render_battle();
		std::cin >> c;
		//SDL_BlitSurface(pkmn, NULL, );
		//std::cout << "j: " << j << std::endl;
	//}
	//std::cout << i << std::endl;
	//}
	//std::cout << "vo: " << battle_field.w << std::endl;

	return;
}
void Map_better::render_battle() {
	int c;
	SDL_RenderCopy(Game::renderer, pkmn, &p_src, &p_dest);
	SDL_RenderPresent(Game::renderer);
	SDL_RenderCopy(Game::renderer, pkmn, &o_src, &o_dest);
	std::cout << "pagauna" << std::endl;
	SDL_RenderPresent(Game::renderer);
}