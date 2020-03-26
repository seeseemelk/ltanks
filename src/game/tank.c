/**
 * The Tank class.
 */

#include "game/tank.h"
#include "cdefs.h"
#include <stdlib.h>
#include <math.h>

struct tank_t
{
	float drive_direction;
	float cannon_direction;
	float drive_speed;
	u16 x;
	u16 y;
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
void tank_set_location(Tank tank, u16 x, u16 y)
{
	tank->x = x;
	tank->y = y;
}

/**
 * Sets the speed and direction of the tank.
 *
 * @param tank The tank
 * @param direction The direction of the tank (in degrees)
 * @param speed The speed of the tank (in units per seconds)
 */
void tank_set_motor(Tank tank, float direction, float speed)
{
	if (speed < 0)
	{
		speed = -speed;
		direction += M_PI/2;
	}

	//if (speed > 1000)
		//speed = 1000;

	tank->drive_direction = direction;
	tank->drive_speed = speed;
}

/**
 * Moves the tank according to it's speed and location.
 *
 * @param tank The tank to move.
 * @param deltatime The amount of time that has passed since the last movement.
 */
void tank_move(Tank tank, float deltatime)
{
	tank->y += sin(tank->drive_direction) * tank->drive_speed * deltatime;
	tank->x += cos(tank->drive_direction) * tank->drive_speed * deltatime;
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
