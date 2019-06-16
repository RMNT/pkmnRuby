#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>
#include <ctime>
#include <string>
#include <SDL_image.h>
#include "map.h"
#include "Pokemon.h"

#define FIRE 1
#define NORMAL 2

#define UP_KEY 72
#define DOWN_KEY 80
#define LEFT_KEY 75
#define RIGHT_KEY 77

Pokemon::Pokemon() : b_att(0), b_def(0), b_sp_att(0), b_sp_def(0) {
}
 Pokemon::~Pokemon() {
}
void Pokemon::newLevel() {
	++(this->level);
	this->hp = (((int)(this->b_hp + this->iv) * 2 + (int)(sqrt(this->ev) / 4))*this->level / 100) + this->level + 10;
	this->att = ((((int)this->b_att + this->iv) * 2 + (int)(sqrt(this->ev) / 4))*(this->level) / 100) + 5;
	this->def = ((((int)this->b_def + this->iv) * 2 + (int)(sqrt(this->ev) / 4))*(this->level) / 100) + 5;
	this->sp_att = ((((int)this->b_sp_att + this->iv) * 2 + (int)(sqrt(this->ev) / 4))*(this->level) / 100) + 5;
	this->sp_def = ((((int)this->b_sp_def + this->iv) * 2 + (int)(sqrt(this->ev) / 4))*(this->level) / 100) + 5;
	this->spd = ((((int)this->b_spd + this->iv) * 2 + (int)(sqrt(this->ev) / 4))*(this->level) / 100) + 5;

}
void Pokemon::attack() {
	std::cout << "pokemonas puola";
}
std::string Pokemon::getName() {
	return *name;
}
int Pokemon::get_spd() {
	return this->spd;
}

 Torchic::Torchic() {
	type = FIRE;
	level = 5;
	b_hp = 45;
	b_att = 60;
	b_def = 40;
	b_sp_att = 70;
	b_sp_def = 50;
	b_spd = 45;
	iv = 31;
	ev = 252;
	exp = 0;
	level--;
	this->newLevel();
	name = new std::string("Torchic");
	back = "user.png";
}
void Torchic::attack() {
	std::cout << this->getName() << " kerta";
}
void Torchic::sp_attack() {
}
std::string Torchic::getName() {
	return "Degantis visciukas";
}

Zigzagoon::Zigzagoon() {
	srand((int)time(NULL));

	type = NORMAL;

	level = (int)(3 + (std::rand() % (8 - 3 + 1))) - 1;

	name = new std::string("Zigzagoon");
	b_hp = 38;
	b_att = 30;
	b_def = 41;
	b_sp_att = 30;
	b_sp_def = 41;
	b_spd = 60;
	iv = 31;
	ev = 252;
	exp = 0;
	this->newLevel();
	front = "user.png";
}
void Zigzagoon::attack() {
	std::cout << this->getName() << " kanda";
}
void Zigzagoon::sp_attack() {
}

std::string Zigzagoon::getName() {
	return "rudas meskenas";
}

 Wurmple::Wurmple() {
	srand((int)time(NULL));

	type = NORMAL;

	level = (int)(3 + (std::rand() % (7 - 3 + 1))) - 1;

	name = new std::string("Wurmple");
	b_hp = 45;
	b_att = 45;
	b_def = 35;
	b_sp_att = 20;
	b_sp_def = 30;
	b_spd = 20;
	iv = 31;
	ev = 252;
	exp = 0;
	this->newLevel();
	front = "user.png";
}
void Wurmple::attack() {
	std::cout << this->getName() << " egzistuoja";
}
void Wurmple::sp_attack() {
}
std::string Wurmple::getName() {
	return "viksras";
}
