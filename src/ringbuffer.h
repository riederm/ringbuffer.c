#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdbool.h>

#define MAX_RING_SIZE 16

typedef struct tag_name {
   int size;
   int data[MAX_RING_SIZE];  //the actual stack data
} RingBuffer;


RingBuffer* ring_create(int maxSize);
void ring_delete(RingBuffer* buffer);

int ring_size(RingBuffer* ringBuffer);
bool ring_add(RingBuffer* ringBuffer,int element);



#endif