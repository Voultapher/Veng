#pragma once

#include <vector>
#include <initializer_list>

#include "Bullet.h"
#include "Player.h"


struct GameObjects{
	std::vector<Player *> players;
	std::vector<Bullet *> bullets;

	template<typename T>
	bool getCurrentObject(){
		T currentObject = players[i];
		return true;
	}

	int i = 0;
	bool forAll = true;

};