#ifndef GAME_H
#define GAME_H

#include "gfx/gfx.h"

void game_init(void);
void game_print_state(void);
void game_quit(void);
bool game_step(void);

// Game play related stuff
void game_loaded(void);
void game_handle_key(key_t key);

#endif
