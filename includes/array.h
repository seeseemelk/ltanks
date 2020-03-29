/**
 * Dynamic array handling
 */
#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>
#include <stddef.h>

typedef struct array_t* Array;

Array array_new(void);
void array_free(Array array);
size_t array_size(Array array);
void* array_get(Array array, size_t index);
void array_push(Array array, void* element);
void array_remove_element(Array array, void* element);

#endif /* VEC_H_ */
