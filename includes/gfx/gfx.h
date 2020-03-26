#ifndef GFX_GFX_H_
#define GFX_GFX_H_

#include <stdbool.h>

enum keycode_t
{
	KC_ESCAPE,
	KC_UNKNOWN
};
typedef enum keycode_t keycode_t;

typedef struct
{
	keycode_t key;
	char ch;
} key_t;

void gfx_run(void);
void gfx_quit(void);
void gfx_set_char(unsigned int x, unsigned int y, char c);
void gfx_print(unsigned int x, unsigned int y, const char* str);
unsigned int gfx_width(void);
unsigned int gfx_height(void);

#endif /* GFX_GFX_H_ */
