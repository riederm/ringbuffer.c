#include "ringbuffer.h"
#include <stddef.h>
#include <stdlib.h>

RingBuffer *ring_create(int maxSize) {
  RingBuffer *buffer = (RingBuffer *)malloc(sizeof(RingBuffer));
  return buffer;
}

void ring_delete(RingBuffer *buffer) {
}

void ring_add(RingBuffer *buffer, int element) {
}

bool ring_remove(RingBuffer *buffer, int *result) {
  return false;
}
