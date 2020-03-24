#include "game/game.h"
#include "game/world.h"
#include "game/tank.h"
#include <stdio.h>

struct game_t
{
	World world;
};

static struct game_t g_game;

void game_init(void)
{
	g_game.world = world_new();

	Tank tank = tank_new();
	world_add_tank(g_game.world, tank);
}

void game_print_state()
{
	range_t iterator = world_get_tanks(g_game.world);
	Tank tank;
	size_t tank_count = 0;
	while ((tank = range_next(&iterator)) != NULL)
	{
		puts("Got a tank");
		tank_count++;
	}
	printf("There are %zu tanks\n", tank_count);
}
