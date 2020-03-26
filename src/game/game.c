#include "game/game.h"
#include "game/world.h"
#include "game/tank.h"
#include "game/internal.h"
#include "vm/vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct game_t g_game;

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
	g_game.vm = vm_new();

	Tank tank = tank_new();
	tank_set_location(tank, rand(), rand());

	vm_set_tank(g_game.vm, tank);
	vm_set_program(g_game.vm,
			"local d = 0\n"
			"function loop()\n"
			"  move(d, 10)\n"
			"  d = d + 10\n"
			"end");

	world_add_tank(g_game.world, tank);
}

/**
 * Frees game resources.
 */
void game_quit(void)
{
	vm_free(g_game.vm);
	world_free(g_game.world);
}

/**
 * Runs a single step of the game.
 */
void game_step(void)
{
	// Run VM state
	vm_run(g_game.vm);

	// Move all tanks
	range_t iterator = world_get_tanks(g_game.world);
	Tank tank;
	while ((tank = range_next(&iterator)) != NULL)
		tank_move(tank, 1.0f);

	// Print state
	game_print_state();
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
}
