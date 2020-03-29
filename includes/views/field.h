#ifndef VIEWS_FIELD_H_
#define VIEWS_FIELD_H_

#include "game/tank.h"
#include "game/missile.h"

void field_show(void);
void field_render_tank(Tank tank);
void field_render_missile(Missile missile);
void field_render_explosion(u16 x, u16 y, float radius);

#endif /* VIEWS_FIELD_H_ */
