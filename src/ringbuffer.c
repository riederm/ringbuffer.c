#include "ringbuffer.h"
#include <stddef.h>
#include <stdlib.h>

/*
* instantiates a new ring buffer and returns a pointer to it.
* must be free'ed using ring_delete(...)
*/
RingBuffer *ring_create(int maxSize)
{
    RingBuffer *buffer = (RingBuffer *)malloc(sizeof(RingBuffer));   
    buffer->size = -1;
    return buffer;
}

void ring_delete(RingBuffer *buffer)
{
}

/*
* adds the element to the ring buffer
*/
void ring_add(RingBuffer *buffer, int element)
{
  
}

/*
* adds the element to the ring buffer
*/
bool ring_remove(RingBuffer *buffer, int* result)
{
  
}
