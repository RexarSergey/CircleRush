#include "FlyingBlock.h"


FlyingBlock::FlyingBlock(const int size, const int a, const int b, const bool death) : _size(size), _is_death_block(death)
{
	//_y = SCREEN_HEIGHT - _size;
	_y_start = SCREEN_HEIGHT;
	_y_end = -_size;

	// for good randomization
	for (size_t i = 0; i < 10; i++)
	{
		_x_start = random_in_range(a, b);
		_x_end = random_in_range(a, b) - _size;
	}

	// digit for movement direction
	_dig = _x_start > _x_end ? -1.f : 1.f;
}

void FlyingBlock::draw_block()
{
	unsigned int y_min = clamp((int)_y_start, 0, SCREEN_HEIGHT);
	unsigned int x_min = clamp((int)_x_start, 0, SCREEN_WIDTH);

	unsigned int y_max = clamp((int)(_y_start + _size), 0, SCREEN_HEIGHT);
	unsigned int x_max = clamp((int)(_x_start + _size), 0, SCREEN_WIDTH);


	for (unsigned int i = y_min; i <= y_max; i++)
	{
		for (unsigned int j = x_min; j <= x_max; j++)
		{
			buffer[i][j] = _is_death_block ? DEATH_BLOCK_COLOR : POINT_BLOCK_COLOR;
		}
	}
}

void FlyingBlock::move_block(const float speed)
{
	// |y0 - y0|, |x0 - x1|
	float y_delta = std::abs(_y_end - _y_start);
	float x_delta = std::abs(_x_end - _x_start);

	// length between coordinated
	float squared = std::sqrt(x_delta * x_delta + y_delta * y_delta);

	// normalization
	float y_normalize = y_delta / squared;
	float x_normalize = x_delta / squared;

	// movement from (x0, y0) to (x1, y1)
	_y_start -= (speed * y_normalize);
	_x_start += (speed * x_normalize * _dig);
}

bool FlyingBlock::is_moving()
{
	return (_x_start > _x_end) && (_y_start > _y_end);
}

bool FlyingBlock::overlap(Player* p)
{
	int p_x_left = p->get_x();
	int p_y_up = p->get_y();
	int p_x_right = p_x_left + p->get_size();
	int p_y_down = p_y_up + p->get_size();

	// check if right or left object side overlapping player
	// AND
	// up or down object side overlapping player
	return (((p_x_left <= _x_start) && (_x_start <= p_x_right)) || ((p_x_left <= _x_start + _size) && (_x_start + _size <= p_x_right)))
		&& (((p_y_up <= _y_start) && (_y_start <= p_y_down)) || ((p_y_up <= _y_start + _size) && (_y_start + _size <= p_y_down)));
}

bool FlyingBlock::get_is_death_block()
{
	return _is_death_block;
}
