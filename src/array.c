#include "array.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

struct entry_t
{
	void* entry;
};

/**
 * A generic container implemented as a dynamically growing array.
 */
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
 * Grows the array.
 *
 * Grows the array so that new items can be added to it.
 *
 * @param array The array to grow.
 */
static void array_grow(Array array)
{
	if (array->capacity == 0)
		array->capacity = 1;
	else
		array->capacity *= 2;
	array->memory = realloc(array->memory, array->capacity * sizeof(struct entry_t));
}

/**
 * Creates a new array.
 *
 * @return The newly created array.
 */
Array array_new(void)
{
	Array array = malloc(sizeof(struct array_t));
	array->memory = NULL;
	array->size = 0;
	array->capacity = 0;
	return array;
}

/**
 * Frees an array.
 *
 * @param array The array to free.
 */
void array_free(Array array)
{
	free(array->memory);
	free(array);
}

/**
 * Gets the size of the array.
 *
 * Counts the number of items that are currently stored
 * inside of the array.
 *
 * @param array The array to check.
 * @return The number of items inside of the array.
 */
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
	if (index >= array->size)
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
	if (index >= array->size)
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
	array->size++;
	array_set(array, array->size - 1, element);
}

/**
 * Removes an element from an array, shifting all later
 * elements.
 *
 * @param array The array containing the element.
 * @param element The element to remove.
 */
void array_remove_element(Array array, void* element)
{
	size_t size = array->size;
	struct entry_t* memory = array->memory;

	size_t i = 0;
	for (; i < size; i++)
	{
		if (memory[i].entry == element)
			break;
	}
	i++;
	for (; i < size; i++)
		memory[i-1].entry = memory[i].entry;
	array->size--;
}
