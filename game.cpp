#include <iostream>
#include <SDL.h>
#include "Pokemon.h"
#include "map.h"
#include "game.h"
#include <fstream>
#include <SDL_image.h>
#include<string>
#include <vector>
#include <algorithm>

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::ev;

std::vector<int> Game::points;
std::vector<std::string> Game::userNames;
std::string Game::userName;

void Game::getName() {
	std::string name = "";

	std::cout << "Iveskite savo varda (max 20 zenklu): ";
	std::getline(std::cin, name);
	userName = name;
}
void Game::loadUserFile() {
	std::fstream userData("results.txt");

	std::string temp_name;
	int temp_points;

	if (userData.good()) {
		while (!userData.eof()) {
			userData >> temp_name >> temp_points;
			userNames.push_back(temp_name);
			points.push_back(temp_points);
		}
	}
	userData.close();
}
void Game::saveResult() {

	userNames.push_back(userName);
	points.push_back(User::getPkmnCount());

	//TODO correct sorting
	//std::sort(points.rbegin(), points.rend());

	std::fstream res("results.txt", std::ios::out | std::ios_base::app);
	if (res.good()) {
		for(size_t i = 0; i < points.size(); ++i)
			res << userNames[i] << " " << points[i] << std::endl;
	}
	else {
		std::cout << "failo nerado" << std::endl;
	}
	res.close();
}
void Game::printResults() {
	std::cout << std::endl;
	std::cout << userName << " " << User::getPkmnCount() << std::endl;
	std::cout << "-----------------" << std::endl;
	for (size_t i = 0; i < userNames.size(); ++i) {
		std::cout << userNames[i] << " " << points[i] << std::endl;
	}
}
Game::Game() {
}
Game::~Game() {
}
void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow("Pokemon Ruby", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 840, 600, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
			SDL_SetRenderDrawColor(renderer, 255, 236, 230, 100);
		isRunning = true;
	}
	else {
		isRunning = false;
	}
	map = new Map_better();
	map->init();
	loadUserFile();
	getName();
}
void Game::handleEvents() {
	SDL_PollEvent(&ev);
	switch (ev.type) {
	case SDL_KEYDOWN:
		switch (ev.key.keysym.sym) {
		case SDLK_m:
			printResults();
			break;
		default:
			break;
		}
		break;
	case SDL_QUIT:
		isRunning = false;
		saveResult();
		break;
	default:
		break;
	}
}
void Game::update() {
	static int prev_x = -1, prev_y = -1;

	if (!(map->isGrass())) {
		prev_x = map->player->whatIsX();
		prev_y = map->player->whatIsY();
		map->player->update();
	}
	else {
		if (prev_x != map->player->whatIsX()) {
			map->findpokemon();
			prev_x = map->player->whatIsX();
		}
		if (prev_y != map->player->whatIsY()) {
			map->findpokemon();
			prev_y = map->player->whatIsY();
		}
		map->player->update();
	}
}
void Game::render() {
	SDL_RenderClear(renderer);
	map->drawMap();
	this->map->player->render();
	SDL_RenderPresent(renderer);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
bool Game::running() {
	return isRunning;
}

SDL_Texture *TextureManager::LoadTexture(const char* texture) {
	SDL_Surface *tempSurface = IMG_Load(texture);
	SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}
void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}
