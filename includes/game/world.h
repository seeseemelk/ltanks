#ifndef GAME_WORLD_H_
#define GAME_WORLD_H_

#include "range.h"
#include "game/tank.h"

/**
 * The game world.
 */
typedef struct world_t* World;

World world_new(void);
void world_free(World world);
range_t world_get_tanks(World world);
void world_add_tank(World world, Tank tank);

#endif /* GAME_WORLD_H_ */
