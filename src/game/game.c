#include "game/game.h"
#include "game/world.h"
#include "game/tank.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct game_t
{
	World world;
};

static struct game_t g_game;

/**
 * Initialises the random number generator.
 */
static void init_rng()
{
	srand(time(NULL));
}

/**
 * Initializes the game.
 */
void game_init(void)
{
	init_rng();
	g_game.world = world_new();

	Tank tank = tank_new();
	tank_move(tank, rand(), rand());
	world_add_tank(g_game.world, tank);
}

/**
 * Frees game resources.
 */
void game_quit(void)
{
	world_free(g_game.world);
}

/**
 * Prints the state of the game.
 */
void game_print_state(void)
{
	range_t iterator = world_get_tanks(g_game.world);
	Tank tank;
	size_t tank_count = 0;
	while ((tank = range_next(&iterator)) != NULL)
	{
		u16 x = tank_get_x(tank);
		u16 y = tank_get_y(tank);
		printf("Tank %zu is at location [%d, %d]\n", tank_count, x, y);
		tank_count++;
	}
	printf("There are %zu tanks\n", tank_count);
}
