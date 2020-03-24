/**
 * The Tank class.
 */

#include "game/tank.h"
#include "cdefs.h"
#include <stdlib.h>

struct tank_t
{
	u16 x;
	u16 y;
	u8 cannon_direction;
};

/**
 * Creates a new tank.
 *
 * @return The newly created tank.
 */
Tank tank_new(void)
{
	Tank tank = malloc(sizeof(struct tank_t));
	tank->x = 0;
	tank->y = 0;
	return tank;
}

/**
 * Frees an existing tank.
 *
 * @param tank The tank to free.
 */
void tank_free(Tank tank)
{
	free(tank);
}

/**
 * Moves a tank to a new location.
 */
void tank_move(Tank tank, u16 x, u16 y)
{
	tank->x = x;
	tank->y = y;
}

/**
 * Gets the X coordinate of the tank.
 *
 * @param tank
 * @return The X coordinate.
 */
u16 tank_get_x(Tank tank)
{
	return tank->x;
}

/**
 * Gets the Y coordinate of the tank.
 *
 * @param tank
 * @return The Y coordinate.
 */
u16 tank_get_y(Tank tank)
{
	return tank->y;
}
