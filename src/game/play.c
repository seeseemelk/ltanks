#include "game/game.h"
#include "game/internal.h"
#include "gfx/gfx.h"
#include "views/field.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define CLOCK_TO_MS(x) (x / (CLK_TCK / 1000UL))
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
	//printf("Difference: %ld\n", CLOCK_TO_MS(difference));
	if (CLOCK_TO_MS(difference) <= 100)
		return false;
	previous_time = current_time;

	// Run VM state
	vm_run(g_game.vm);

	// Move and render all tanks
	range_t iterator = world_get_tanks(g_game.world);
	Tank tank;

	field_show();
	while ((tank = range_next(&iterator)) != NULL)
	{
		tank_move(tank, 1.0f);
		field_show_tank(tank);
	}

	return true;
}
