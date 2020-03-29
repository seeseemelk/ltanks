#include "game/game.h"
#include "game/internal.h"
#include "gfx/gfx.h"
#include "views/field.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define CLOCK_TO_MS(x) (x / (CLOCKS_PER_SEC / 1000UL))

static clock_t previous_time;

/**
 * Executed when the game is loaded.
 */
void game_loaded(void)
{
	previous_time = clock();
	gfx_print(0, 0, "Hello, world!\nFrom the game...");
}

/**
 * Handles a single key press.
 */
void game_handle_key(key_t key)
{
	switch (key.key)
	{
	case KC_ESCAPE:
		gfx_quit();
		break;
	case KC_UNKNOWN:
		break;
	}
}

/**
 * Runs a single step of the game.
 */
bool game_step(void)
{
	// Check if an update is needed
	clock_t current_time = clock();
	clock_t difference = current_time - previous_time;
	if (CLOCK_TO_MS(difference) <= 100)
		return false;
	previous_time = current_time;

	// Run VM state
	size_t vm_count = array_size(g_game.vm);
	for (size_t i = 0; i < vm_count; i++)
	{
		vm_run(array_get(g_game.vm, i));
	}

	// Move and render all tanks
	field_show();
	Array tanks = world_get_tanks(g_game.world);
	size_t tank_count = array_size(tanks);
	for (size_t i = 0; i < tank_count; i++)
	{
		Tank tank = array_get(tanks, i);
		tank_update(tank);
		field_render_tank(tank);
	}

	// Move and render all missiles
	Array missiles = world_get_missiles(g_game.world);
	size_t missile_count = array_size(missiles);
	for (size_t i = 0; i < missile_count; i++)
	{
		Missile missile = array_get(missiles, i);
		if (missile_move(missile))
		{
			world_explode(g_game.world, missile_get_x(missile), missile_get_y(missile));
			array_remove_element(missiles, missile);
			i--;
			missile_count--;
			missile_free(missile);
		}
		else
			field_render_missile(missile);
	}

	return true;
}
