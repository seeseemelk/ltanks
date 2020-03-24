#include "range.h"

range_t range_new(void* (*next)(void*), void* arg)
{
	range_t range;
	range.arg = arg;
	range.next_callback = next;
	return range;
}

void* range_next(range_t* range)
{
	return range->next_callback(range->arg);
}
