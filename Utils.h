#pragma once

#include <cstdlib>

// changable params
#define BACKGROUND_COLOR bgra_to_int(1, 0, 242, 255)
#define RING_COLOR bgra_to_int(1, 0, 0, 0)
#define PLAYER_COLOR bgra_to_int(1, 255, 255, 255)
#define DEATH_BLOCK_COLOR bgra_to_int(1, 0, 0, 0)
#define POINT_BLOCK_COLOR bgra_to_int(1, 255, 255, 255)
#define POINT_COUNTER_COLOR bgra_to_int(1, 255, 255, 255)

constexpr auto RING_RADIUS = 150;

constexpr auto PLAYER_SPEED = 4;
constexpr auto PLAYER_SIZE = 30;

constexpr auto BLOCK_SPEED = 350;
constexpr auto BLOCK_SIZE = 30;

constexpr auto NUMBER_PIXEL_SIZE = 15;
constexpr auto POINT = 1;


// numbers templates
struct numbers {
	const bool zero[5][3] = {
		{1,1,1},
		{1,0,1},
		{1,0,1},
		{1,0,1},
		{1,1,1}
	};

	const bool one[5][3] = {
		{0,0,1},
		{0,0,1},
		{0,0,1},
		{0,0,1},
		{0,0,1}
	};

	const bool two[5][3] = {
		{1,1,1},
		{0,0,1},
		{1,1,1},
		{1,0,0},
		{1,1,1}
	};

	const bool three[5][3] = {
		{1,1,1},
		{0,0,1},
		{0,1,1},
		{0,0,1},
		{1,1,1}
	};

	const bool four[5][3] = {
		{1,0,1},
		{1,0,1},
		{1,1,1},
		{0,0,1},
		{0,0,1}
	};

	const bool five[5][3] = {
		{1,1,1},
		{1,0,0},
		{1,1,1},
		{0,0,1},
		{1,1,1}
	};

	const bool six[5][3] = {
		{1,1,1},
		{1,0,0},
		{1,1,1},
		{1,0,1},
		{1,1,1}
	};

	const bool seven[5][3] = {
		{1,1,1},
		{0,0,1},
		{0,0,1},
		{0,0,1},
		{0,0,1}
	};

	const bool eight[5][3] = {
		{1,1,1},
		{1,0,1},
		{1,1,1},
		{1,0,1},
		{1,1,1}
	};

	const bool nine[5][3] = {
		{1,1,1},
		{1,0,1},
		{1,1,1},
		{0,0,1},
		{1,1,1}
	};
};

// convert function
static uint32_t bgra_to_int(unsigned const char a,
	unsigned const char r,
	unsigned const char g,
	unsigned const char b)
{
	return (a << 24) + (r << 16) + (g << 8) + b;
}

// random number generator
template<typename T>
static T random_in_range(const T min, const T max)
{
	return (min + std::rand() % (max - min + 1));
}

// clamp
template<typename T>
static T clamp(const T number, const T min, const T max)
{
	if (number > max) return max;
	if (number < min) return min;
	return number;
}

// draw pixel of size
static void color_pixel(unsigned const int min_x, unsigned const int max_x,
	unsigned const int min_y, unsigned const int max_y)
{
	for (unsigned int i = min_y; i < max_y; i++)
	{
		for (unsigned int j = min_x; j < max_x; j++)
		{
			buffer[i][j] = POINT_COUNTER_COLOR;
		}
	}
}

// color number by template
static void color_number(unsigned const int x, unsigned const int y,
	unsigned const int size, const bool(&number)[5][3])
{
	for (unsigned int i = 0; i < 5; i++)
	{
		for (unsigned int j = 0; j < 3; j++)
		{
			if (number[i][j])
				color_pixel(x + j * size, x + (j + 1) * size,
					y + i * size, y + (i + 1) * size);
		}
	}
}

// draw number
static void draw_number(int points)
{
	numbers num_template;

	unsigned int size = NUMBER_PIXEL_SIZE;
	unsigned int num = points;

	unsigned int x = SCREEN_WIDTH - (15 + 3 * size);
	unsigned int y = 15;

	do
	{
		switch (num % 10)
		{
		case 0:
			color_number(x, y, size, num_template.zero);
			break;

		case 1:
			color_number(x, y, size, num_template.one);
			break;

		case 2:
			color_number(x, y, size, num_template.two);
			break;

		case 3:
			color_number(x, y, size, num_template.three);
			break;

		case 4:
			color_number(x, y, size, num_template.four);
			break;

		case 5:
			color_number(x, y, size, num_template.five);
			break;

		case 6:
			color_number(x, y, size, num_template.six);
			break;

		case 7:
			color_number(x, y, size, num_template.seven);
			break;

		case 8:
			color_number(x, y, size, num_template.eight);
			break;

		case 9:
			color_number(x, y, size, num_template.nine);
			break;

		default:
			break;
		}

		x -= (10 + 3 * size);
		num /= 10;
	} while (num != 0);
}

