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
 * Loads an extra bot.
 */
static void load_bot(const char* path)
{
	Tank tank = tank_new(g_game.next_bot_id);
	g_game.next_bot_id++;

	tank_set_location(tank, rand(), rand());

	VM vm = vm_new_from_file(path);
	tank_set_vm(tank, vm);

	world_add_tank(g_game.world, tank);
}

/**
 * Initializes the game.
 */
void game_init(void)
{
	init_rng();

	g_game.world = world_new();
	g_game.next_bot_id = 0;

	load_bot("bots/roamer.lua");
	load_bot("bots/spammer.lua");

	for (int i = 0; i < 20; i++)
		load_bot("bots/dummy.lua");
}

/**
 * Frees game resources.
 */
void game_quit(void)
{
	Array tanks = world_get_tanks(g_game.world);
	size_t tank_count = array_size(tanks);
	for (size_t i = 0; i < tank_count; i++)
	{
		Tank tank = array_get(tanks, i);
		vm_free(tank_get_vm(tank));
	}
	world_free(g_game.world);
}

/**
 * Prints the state of the game.
 */
void game_print_state(void)
{
	Array tanks = world_get_tanks(g_game.world);
	size_t tank_count = array_size(tanks);
	for (size_t i = 0; i < tank_count; i++)
	{
		Tank tank = array_get(tanks, i);
		u16 x = tank_get_x(tank);
		u16 y = tank_get_y(tank);
		printf("Tank %zu is at location [%d, %d]\n", tank_count, x, y);
		tank_count++;
	}
}
