#ifndef GAME_MISSILE_H_
#define GAME_MISSILE_H_

#include "game/types.h"
#include "cdefs.h"
#include <stdbool.h>

Missile missile_new(u16 x, u16 y, float direction, float distance);
void missile_free(Missile missile);

u16 missile_get_x(Missile missile);
u16 missile_get_y(Missile missile);

bool missile_move(Missile missile);

#endif /* GAME_MISSILE_H_ */
