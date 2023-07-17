#include "Engine.h"
#include "Utils.h"
#include "Player.h"
#include "FlyingBlock.h"
#include <stdlib.h>
#include <memory.h>
#include <cmath>


// game data
Player* p1; // this is one player but it separated in to two objects
Player* p2;

FlyingBlock* fb; // flying block

float dir; // player movement direction
bool isPressed; // flag for button

unsigned short points; // player points


// spawn random type block
void spawn_block()
{
	if (fb) delete fb;

	int rand_num = 1 + rand() % 100;
	// death type block: ~60% chance
	// point type block: ~40% chance
	bool block_type = rand_num <= 60 ? true : false;

	fb = new FlyingBlock(BLOCK_SIZE,
		SCREEN_WIDTH / 2 - RING_RADIUS,
		SCREEN_WIDTH / 2 + RING_RADIUS,
		block_type);
}


// destroy player objects
void kill_player()
{
	delete p1;
	delete p2;

	p1 = nullptr;
	p2 = nullptr;
}


// overlap function
void overlap()
{
	if (fb->overlap(p1) || fb->overlap(p2))
	{
		if (fb->get_is_death_block())
		{
			kill_player();
		}
		else
		{
			points += POINT;
			delete fb;
			fb = nullptr;
		}
	}
}


// initialize game data in this function
void initialize()
{
	// for rand()
	srand(time(0));

	p1 = new Player(PLAYER_SIZE);
	p2 = new Player(PLAYER_SIZE);

	fb = nullptr;

	dir = 1.f;
	isPressed = false;

	points = 0;
}


// restart game
void restart()
{
	// free memory
	finalize();
	// initialize game data again
	initialize();
}


// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
	// change player dirrection
	if (!isPressed && is_key_pressed(VK_SPACE))
	{
		dir *= -1.f;
		isPressed = true;
	}
	if (!is_key_pressed(VK_SPACE))
		isPressed = false;

	// restart game
	if (is_key_pressed('R'))
		restart();

	// do smth only if the player object still exists
	if (p1 && p2)
	{
		// move player
		p1->move(PLAYER_SPEED * dt * dir, 1);
		p2->move(PLAYER_SPEED * dt * dir, -1);

		// spawn flying block
		if (!fb)
			spawn_block();

		// move flying block only if it is exists
		if (fb && fb->is_moving())
		{
			fb->move_block(BLOCK_SPEED * dt);
			// check overlap
			overlap();
		}
		else // if fb is not moving
		{
			delete fb;
			fb = nullptr;
		}
	}

	if (is_key_pressed(VK_ESCAPE))
		schedule_quit_game();
}


// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
	// clear backbuffer
	memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

	// draw background
	for (size_t i = 0; i < SCREEN_HEIGHT; i++)
	{
		for (size_t j = 0; j < SCREEN_WIDTH; j++)
		{
			buffer[i][j] = BACKGROUND_COLOR;
		}
	}

	// draw point counter
	draw_number(points);

	// draw ring
	for (size_t i = 0; i < 360; i++)
	{
		int x = (SCREEN_HEIGHT / 2) + RING_RADIUS * std::cos(i);
		int y = (SCREEN_WIDTH / 2) + RING_RADIUS * std::sin(i);
		buffer[x][y] = RING_COLOR;
	}

	// draw player
	if (p1 && p2)
	{
		p1->draw_player();
		p2->draw_player();
	}

	// draw flying block
	if (fb)
		fb->draw_block();
}


// free game data in this function
void finalize()
{
	delete p1;
	delete p2;
	delete fb;
}

