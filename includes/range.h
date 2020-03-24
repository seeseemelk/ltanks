#ifndef RANGE_H_
#define RANGE_H_

struct range_t
{
	void* (*next_callback)(void*);
	void* arg;
	void* current_element;
};
typedef struct range_t range_t;

/**
 * @brief Creates a new range.
 * @param next A callback that will either return the next
 *   element in the range, or `NULL` if there are no next elements.
 * @param arg An extra argument that should be passed to the callback.
 */
range_t range_new(void* (*next)(void*), void* arg);

/**
 * @brief Returns the next item in a range.
 *
 * @param range The range to iterate over.
 *
 * @return The next item in the range.
 * @return `NULL` if the end of the range has been reached.
 */
void* range_next(range_t* range);


#endif /* RANGE_H_ */
