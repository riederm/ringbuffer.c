#include "ringbuffer.h"
#include <stddef.h>
#include <stdlib.h>

/*
* instantiates a new ring buffer and returns a pointer to it.
* must be free'ed using ring_delete(...)
*/
RingBuffer *ring_create( int maxSize)
{
    RingBuffer *buffer = (RingBuffer *)malloc(sizeof(RingBuffer));   
    buffer->size = 0;
    buffer->data = malloc(maxSize* sizeof (int));
    for (int i = 0; i < maxSize; i++)
    {
        buffer->data[i] = 0;
    }
    
    buffer->maxSize = maxSize;

    buffer->lastReadIndex=0;
    buffer->lastWriteIndex=0;

    return buffer;
}

void ring_delete(RingBuffer *buffer)
{
     free(buffer->data);
     free(buffer);
}

void moveIndex(RingBuffer* buffer, int* actualIndex){
     *actualIndex = (*actualIndex+ 1 ) % buffer->maxSize;
}

bool isFull(RingBuffer* buffer){
    return buffer->size==buffer->maxSize;
}

bool isEmpty(RingBuffer* buffer){
 return buffer->size == 0;
}

/*
* adds the element to the stack
*/
void ring_add(RingBuffer *buffer, int element)
{
    //calc new size
    if(!isFull(buffer)){
        buffer->size++;
    }
    //write element
    buffer->data[buffer->lastWriteIndex]=element;
  
  //lets see if we need to move the read-pointer as well (overflow)
    if(buffer->lastWriteIndex == buffer->lastReadIndex && ! isEmpty(buffer)){
        moveIndex(buffer,&buffer->lastReadIndex);
    }

    //move write-pointer
    moveIndex(buffer,&buffer->lastWriteIndex);

}


bool ring_remove(RingBuffer* buffer,int* result){
    if(buffer->size == 0){
        return false;
    }

    *result = buffer->data[buffer->lastReadIndex];
    moveIndex(buffer,&buffer->lastReadIndex);
    buffer->size--;

    return true;
}
