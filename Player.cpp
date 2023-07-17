#include "Player.h"


Player::Player(const int size) : _size(size) {}

void Player::draw_player()
{
	for (unsigned int i = _y_start; i <= _y_start + _size; i++)
	{
		for (unsigned int j = _x; j <= _x + _size; j++)
		{
			buffer[i % SCREEN_HEIGHT][j % SCREEN_WIDTH] = PLAYER_COLOR;
		}
	}
}

void Player::move(const float alpha, const int pos)
{
	// parameter for shifting coordinates from the corner to the center of the object
	int shift = _size % 2 == 0 ? _size / 2 : (_size / 2) + 1;

	// circular motion
	_angle += alpha;
	_y_start = (SCREEN_HEIGHT / 2) + RING_RADIUS * std::cos(_angle) * pos - shift;
	_x = (SCREEN_WIDTH / 2) + RING_RADIUS * std::sin(_angle) * pos - shift;
}

float Player::get_x()
{
	return _x;
}

float Player::get_y()
{
	return _y_start;
}

float Player::get_size()
{
	return _size;
}
