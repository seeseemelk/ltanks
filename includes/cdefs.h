#ifndef HEADER_UTILS
#define HEADER_UTILS

#include <stdint.h>

#define UNUSED(x) ((void) x)
#define M_PI 3.14159265358979323846264338327950288419716939937510582097

typedef uint16_t u16;
typedef uint8_t u8;
typedef const char* String;

/**
 * Returns the absolute value of the difference of `a` and `b`.
 */
static inline unsigned int absdiff(unsigned int a, unsigned int b)
{
	return (a > b) ? (a - b) : (b - a);
}

#endif /* HEADER_UTILS */
