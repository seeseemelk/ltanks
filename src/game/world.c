#include "game/world.h"
#include "game/tank.h"
#include "array.h"
#include "range.h"
#include <stdlib.h>

struct world_t
{
	Array tanks;
};

struct tank_iterator
{
	Array tanks;
	size_t index;
};
typedef struct tank_iterator* TankIterator;

static void* _world_next_tank(void* arg)
{
	TankIterator iterator = arg;
	if (iterator->index >= array_size(iterator->tanks))
		return NULL;
	return array_get(iterator->tanks, iterator->index++);
}

World world_new(void)
{
	World world = malloc(sizeof(struct world_t));
	world->tanks = array_new();
	return world;
}

void world_free(World world)
{
	free(world);
}

range_t world_get_tanks(World world)
{
	TankIterator iterator = malloc(sizeof(TankIterator));
	iterator->tanks = world->tanks;
	iterator->index = 0;
	range_t range = range_new(_world_next_tank, iterator);
	return range;
}

void world_add_tank(World world, Tank tank)
{
	array_push(world->tanks, tank);
}