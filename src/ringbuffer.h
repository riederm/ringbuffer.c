#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <stdbool.h>


typedef struct tag_name {
   int size;
   int data[16];  //the actual ring buffer data
} RingBuffer;


RingBuffer* ring_create(int maxSize);
void ring_delete(RingBuffer* buffer);


void ring_add(RingBuffer* ringBuffer,int element);
bool ring_remove(RingBuffer* ringBuffer,int* result);



#endif