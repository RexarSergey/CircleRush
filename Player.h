#pragma once

#include "Engine.h"
#include "Utils.h"
#include <cmath>

class Player
{
public:
	Player(const int size);

	// draw function
	void draw_player();

	// move function
	void move(const float alpha, const int pos);

	// getters
	float get_x();
	float get_y();
	float get_size();

private:
	// object size
	int _size;

	// object coordinates
	float _y_start;
	float _x;

	// movement angle
	float _angle = 0.f;
};

