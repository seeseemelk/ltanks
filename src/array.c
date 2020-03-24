#include "array.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

struct entry_t
{
	void* entry;
};

struct array_t
{
	/// A pointer to the start of the array.
	struct entry_t* memory;

	/// The number of elements that are stored in the array.
	size_t size;

	/// The maximum number of elements that can be stored.
	size_t capacity;
};

/**
 * @brief Grows the array.
 */
static void array_grow(Array array)
{
	if (array->capacity == 0)
		array->capacity++;
	else
		array->capacity *= 2;
	array->memory = realloc(array->memory, array->capacity * sizeof(struct entry_t));
}

Array array_new(void)
{
	Array array = malloc(sizeof(struct array_t));
	array->memory = NULL;
	array->size = 0;
	array->capacity = 0;
	return array;
}

void array_free(Array array)
{
	free(array);
}

size_t array_size(Array array)
{
	return array->size;
}

/**
 * @brief Gets an element.
 *
 * Gets an elements from the array.
 * `aborts` the program with an error message if the
 * memory address is out-of-bounds.
 * This method will never return `NULL` unless a `NULL` object
 * was specifically stored in it.
 *
 * @param array The array to retrieve an element from.
 * @param index The index at which the element should be retrieved.
 *
 * @return The element at the given index.
 */
void* array_get(Array array, size_t index)
{
	if (index >= array->capacity)
	{
		fprintf(stderr, "ERROR: Out-of-bounds array read. (index: %zu, size: %zu)\n", index, array->size);
		abort();
	}

	return array->memory[index].entry;
}

/**
 * @brief Sets an element.
 *
 * Sets an element in the array.
 * If the index is out-of-bounds, it will `abort` with an error message.
 *
 * @param array The array to retrieve an element from.
 * @param index The index at which the element should be retrieved.
 * @param element The element to add.
 */
void array_set(Array array, size_t index, void* element)
{
	if (index >= array->capacity)
	{
		fprintf(stderr, "ERROR: Out-of-bounds array write. (index: %zu, size: %zu)\n", index, array->size);
		abort();
	}

	array->memory[index].entry = element;
}

/**
 * @brief Appends an item.
 *
 * Adds an item to the end of the array, potentially increasing the size.
 */
void array_push(Array array, void* element)
{
	if (array->size >= array->capacity)
		array_grow(array);
	array_set(array, array->size, element);
	array->size++;
}
