/**
 * The Tank class.
 */

#include "game/tank.h"
#include "game/world.h"
#include "game/missile.h"
#include "cdefs.h"
#include <stdlib.h>
#include <math.h>

struct tank_t
{
	World world;
	float drive_direction;
	float radar_direction;
	float drive_speed;
	u16 x;
	u16 y;
	unsigned int id;
	unsigned short fire_cooldown;
};

/**
 * Creates a new tank.
 *
 * @return The newly created tank.
 */
Tank tank_new(unsigned int id)
{
	Tank tank = malloc(sizeof(struct tank_t));
	tank->world = NULL;
	tank->x = 0;
	tank->y = 0;
	tank->id = id;
	tank->drive_direction = 0;
	tank->radar_direction = 0;
	tank->drive_speed = 0;
	tank->fire_cooldown = 0;
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
 * Sets the world the tank lives in.
 *
 * @param world The world the tank lives in.
 */
void tank_set_world(Tank tank, World world)
{
	tank->world = world;
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
 * @param direction The direction of the tank (in radians)
 * @param speed The speed of the tank (in units per seconds)
 */
void tank_set_motor(Tank tank, float direction, float speed)
{
	if (speed < 0)
	{
		speed = -speed;
		direction += M_PI/2;
	}

	if (speed > 1000)
		speed = 1000;

	tank->drive_direction = direction;
	tank->drive_speed = speed;
}

/**
 * Sets the radar direction.
 *
 * @param tank The tank
 * @param direction The direction of the radar (in degrees)
 */
void tank_set_radar(Tank tank, float direction)
{
	tank->radar_direction = fmod(direction, (2*M_PI));
}

/**
 * Updates the internal state of the tank.
 * It will also move the tank according to it's speed and location.
 *
 * @param tank The tank to move.
 */
void tank_update(Tank tank)
{
	if (tank->fire_cooldown > 0)
		tank->fire_cooldown--;

	float dy = (sin(tank->drive_direction) * tank->drive_speed);
	float dx = (cos(tank->drive_direction) * tank->drive_speed);

	if ((dy > 0) && (tank->y > UINT16_MAX - dy))
		tank->y = UINT16_MAX;
	else if ((dy < 0) && (tank->y < -dy))
		tank->y = 0;
	else
		tank->y += dy;

	if ((dx > 0) && (tank->x > UINT16_MAX - dx))
		tank->x = UINT16_MAX;
	else if ((dx < 0) && (tank->x < -dx))
		tank->x = 0;
	else
		tank->x += dx;
}

/**
 * Fires a missile in a direction.
 *
 * @param tank The tank that is fires the missile.
 * @param direction The direction to shoot towards.
 * @param distance The distance the missile should fly.
 * @return `true` if a shot was fired.
 * @return `false` if the tank is still in it's cool down phase.
 */
bool tank_fire(Tank tank, float direction, float distance)
{
	if (tank->fire_cooldown > 0)
		return false;
	tank->fire_cooldown = 20;
	Missile missile = missile_new(tank->x, tank->y, direction, distance);
	world_add_missile(tank->world, missile);
	return true;
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

/**
 * Gets the direction the radar is pointing towards.
 *
 * @param tank
 * @return The direction of the cannon, in radians.
 */
float tank_get_radar_direction(Tank tank)
{
	return tank->radar_direction;
}

/**
 * Gets the ID of the tank.
 *
 * @param tank
 * @return The ID of the tank.
 */
unsigned int tank_get_id(Tank tank)
{
	return tank->id;
}
