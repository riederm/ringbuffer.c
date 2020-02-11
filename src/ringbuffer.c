#include "ringbuffer.h"
#include <stddef.h>
#include <stdlib.h>

RingBuffer *ring_create(int maxSize) {
  RingBuffer *buffer = (RingBuffer *)malloc(sizeof(RingBuffer));
  buffer->data = malloc(sizeof(int) * maxSize);
  buffer->nbOfElements = 0;
  buffer->maxSize = maxSize;
  buffer->r = 0;
  buffer->w = 0;
  return buffer;
}

void ring_delete(RingBuffer *buffer) {
	free(buffer->data);
	free(buffer);
}

void ring_add(RingBuffer *buffer, int element) {
  buffer->nbOfElements++;
  buffer->data[buffer->w % buffer->maxSize] = element;
  buffer->w++;

  if (buffer->nbOfElements > buffer->maxSize) {
    int data = 0;
    ring_remove(buffer, &data);
  }
}

bool ring_remove(RingBuffer *buffer, int *result) {
  if (buffer->nbOfElements > 0) {
    *result = buffer->data[buffer->r % buffer->maxSize];
    buffer->r++;
    buffer->nbOfElements--;
    return true;
  }
  return false;
}
