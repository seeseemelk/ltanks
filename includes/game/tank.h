#ifndef GAME_TANK_H_
#define GAME_TANK_H_

#include "game/types.h"
#include "vm/vm.h"
#include "cdefs.h"
#include <stdbool.h>

Tank tank_new(unsigned int id);
void tank_free(Tank tank);

u16 tank_get_x(Tank tank);
u16 tank_get_y(Tank tank);
unsigned int tank_get_id(Tank tank);
float tank_get_radar_direction(Tank tank);

void tank_set_vm(Tank tank, VM vm);
VM tank_get_vm(Tank tank);

void tank_set_world(Tank tank, World world);
void tank_set_location(Tank tank, u16 x, u16 y);
void tank_set_motor(Tank tank, float direction, float speed);
void tank_set_radar(Tank tank, float direction);
void tank_update(Tank tank);
bool tank_fire(Tank tank, float direction, float distance);

#endif /* GAME_TANK_H_ */
