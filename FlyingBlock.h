#pragma once

#include "Engine.h"
#include "Player.h"
#include "Utils.h"
#include <iostream>

class FlyingBlock
{
public:
	FlyingBlock(const int size, const int a, const int b, const bool death);

	// draw function
	void draw_block();

	// move function
	void move_block(const float speed);

	// check if block reached destination
	bool is_moving();

	// overlap function
	bool overlap(Player* p);

	// getter
	bool get_is_death_block();

private:
	int _size;

	float _x_start;
	float _x_end;

	float _y_start;
	float _y_end;

	bool _is_death_block;
	float _dig;
};

