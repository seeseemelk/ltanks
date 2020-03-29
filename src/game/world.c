/**
 * The World class.
 *
 * This class manages the game field or the world.
 * It only concerns itself with stuff directly on the game field,
 * such as tanks and bullets.
 */

#include "game/world.h"
#include "game/tank.h"
#include "game/types.h"
#include "views/field.h"
#include "array.h"
#include <stdlib.h>

struct world_t
{
	Array tanks;
	Array missiles;
};

/**
 * Creates a new world.
 *
 * @return The newly created world.
 */
World world_new(void)
{
	World world = malloc(sizeof(struct world_t));
	world->tanks = array_new();
	world->missiles = array_new();
	return world;
}

/**
 * Frees a world.
 */
void world_free(World world)
{
	array_free(world->tanks);
	array_free(world->missiles);
	free(world);
}

/**
 * Gets all tanks on this world.
 *
 * @return An array containing all tanks on this world.
 */
Array world_get_tanks(World world)
{
	return world->tanks;
}

/**
 * Gets all missiles on this world.
 *
 * @return An array containing all missiles.
 */
Array world_get_missiles(World world)
{
	return world->missiles;
}

/**
 * Adds a tank to the world.
 *
 * @param world The world to add it to.
 * @param tank The tank to add.
 */
void world_add_tank(World world, Tank tank)
{
	tank_set_world(tank, world);
	array_push(world->tanks, tank);
}

/**
 * Adds a missile to the world.
 *
 * @param world The world to add it to.
 * @param missile The missile to add.
 */
void world_add_missile(World world, Missile missile)
{
	array_push(world->missiles, missile);
}

/**
 * Explodes a region of the world.
 *
 * @param world The world.
 * @param x The X-coordinate of the explosion.
 * @param y The Y-coordinate of the explosion.
 * @param radius The radius of the explosion.
 * @param tank_destroyed Callback containing a tank that was destroyed.
 */
void world_explode(World world, u16 x, u16 y, float radius, void (*tank_destroyed)(Tank))
{
	float radius_sqr = radius * radius;
	size_t tank_count = array_size(world->tanks);
	for (size_t i = 0; i < tank_count; i++)
	{
		Tank tank = array_get(world->tanks, i);
		unsigned int dx = absdiff(x, tank_get_x(tank));
		unsigned int dy = absdiff(y, tank_get_y(tank));
		unsigned int distance =  dx*dx + dy*dy;
		if (distance <= radius_sqr)
		{
			array_remove_element(world->tanks, tank);
			i--, tank_count--;
			tank_destroyed(tank);
		}
	}
	field_render_explosion(x, y, radius);
}

