#pragma once
#ifndef  POKEMON_H
#define POKEMON_H

class Pokemon {
public:
	int b_att = 0, b_def = 0, b_sp_att, b_sp_def, b_hp, level, iv, ev, hp, att, def, sp_att, sp_def, b_spd, type, exp, spd;
	std::string* name;
	const char* front, * back;
	void newLevel();
	virtual void attack();
	virtual void sp_attack() = 0;
	int get_spd();
	virtual std::string getName() = 0;
	Pokemon();
	virtual ~Pokemon();
};

class Torchic : public Pokemon {
public:
	Torchic();
	virtual std::string getName();
	virtual void attack();
	virtual void sp_attack();
};

class Zigzagoon : public Pokemon {
public:
	Zigzagoon();
	virtual void attack();
	virtual void sp_attack();
	virtual std::string getName();
};

class Wurmple : public Pokemon {
public:
	Wurmple();
	virtual void attack();
	virtual void sp_attack();
	virtual std::string getName();
};

#endif // ! POKEMON_H
