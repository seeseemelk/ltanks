#ifndef GAME_WORLD_H_
#define GAME_WORLD_H_

#include "game/types.h"
#include "array.h"
#include "cdefs.h"

World world_new(void);
void world_free(World world);
Array world_get_tanks(World world);
Array world_get_missiles(World world);
void world_add_tank(World world, Tank tank);
void world_add_missile(World world, Missile missile);
void world_explode(World world, u16 x, u16 y);

#endif /* GAME_WORLD_H_ */
