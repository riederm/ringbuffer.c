#include "vendor/unity.h"
#include "../src/ringbuffer.h"
#include <stdlib.h>


RingBuffer* buffer;

void setUp(void) {
    buffer = ring_create(5);
}

void tearDown(void) {
    ring_delete(buffer);
}

void test_ring_create(void)
{
  TEST_ASSERT_NOT_NULL(buffer);
  TEST_ASSERT_EQUAL_INT(-1, buffer->size);

  for (size_t i = 0; i < MAX_RING_SIZE; i++) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, buffer->data[i], "data should be 0");
  }
}

void empty_ring_should_have_size_0(void)
{
  int size = buffer->size;
  TEST_ASSERT_EQUAL_INT(0, size);
}

void should_report_number_of_elements(void)
{
    ring_add(buffer,1);
    ring_add(buffer,2);
    ring_add(buffer,3);
     TEST_ASSERT_EQUAL_INT(3, buffer->size);
}

void should_not_exceed_its_maximum_size(void)
{
  int maxSize = 4 ;
    ring_add(buffer,1);
    ring_add(buffer,2);
    ring_add(buffer,3);
    ring_add(buffer,4);
    ring_add(buffer,5);
    TEST_ASSERT_EQUAL_INT(maxSize, buffer->size);
}


int main(void)
{
   UnityBegin("RingBuffer");

   RUN_TEST(test_ring_create);
   RUN_TEST(empty_ring_should_have_size_0);
   RUN_TEST(should_report_number_of_elements);
   RUN_TEST(should_not_exceed_its_maximum_size);

   UnityEnd();
   return 0;
}