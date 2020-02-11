#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdbool.h>


typedef struct tag_name {
   int nbOfElements;    //the number of elements currently stored in the ring
   int* data;  //the actual ring buffer data
} RingBuffer;


/*
 * creates a new ring buffer which is able to store
 * up to [maxSize] elements
 */
RingBuffer* ring_create(int maxSize);

/*
* deletes the ring and the ring's data
*/
void ring_delete(RingBuffer* buffer);

/*
 * adds the element to the ring buffer
 */
void ring_add(RingBuffer* ringBuffer,int element);

/*
* removes and returns the oldest element from ring
*/
bool ring_remove(RingBuffer* ringBuffer,int* result);



#endif