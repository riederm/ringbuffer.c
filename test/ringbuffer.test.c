#include "../src/ringbuffer.h"
#include "vendor/unity.h"
#include <stdlib.h>

const int MAX_nbOfElements = 4;
RingBuffer *buffer;

void setUp(void) { buffer = ring_create(MAX_nbOfElements); }

void tearDown(void) { ring_delete(buffer); }

void test_ring_create(void) {
  TEST_ASSERT_NOT_NULL(buffer);

  /*for (int i = 0; i < MAX_nbOfElements; i++) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, buffer->data[i], "data should be 0");
  }*/
}

void an_empty_ring_should_have_nbOfElements_0(void) {
  int nbOfElements = buffer->nbOfElements;
  TEST_ASSERT_EQUAL_INT(0, nbOfElements);
}

void it_should_report_the_correct_number_of_elements(void) {
  ring_add(buffer, 1);
  ring_add(buffer, 2);
  ring_add(buffer, 3);
  TEST_ASSERT_EQUAL_INT(3, buffer->nbOfElements);
}

void it_should_not_exceed_its_maximum_nbOfElements(void) {
  //...
	TEST_ASSERT_FALSE(true);
}



int main(void) {
  UnityBegin("RingBuffer");

  RUN_TEST(test_ring_create);
  RUN_TEST(an_empty_ring_should_have_nbOfElements_0);
  RUN_TEST(it_should_report_the_correct_number_of_elements);
  RUN_TEST(it_should_not_exceed_its_maximum_nbOfElements);
	
  UnityEnd();
  return 0;
}