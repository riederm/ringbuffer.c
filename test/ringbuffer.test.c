#include "../src/ringbuffer.h"
#include "vendor/unity.h"
#include <stdlib.h>

const int MAX_nbOfElements = 4;
RingBuffer *buffer;

void setUp(void) { buffer = ring_create(MAX_nbOfElements); }

void tearDown(void) { ring_delete(buffer); }

void test_ring_create(void) {
  TEST_ASSERT_NOT_NULL(buffer);

  for (int i = 0; i < MAX_nbOfElements; i++) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, buffer->data[i], "data should be 0");
  }
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

void it_should_return_the_elements_in_a_fifo_order(void) {
  ring_add(buffer, 1);
  ring_add(buffer, 2);
  ring_add(buffer, 3);
  ring_add(buffer, 4);

	int result = 0;

	ring_remove(buffer, &result);
  TEST_ASSERT_EQUAL_INT(1, result);

	ring_remove(buffer, &result);
  TEST_ASSERT_EQUAL_INT(2, result);

	ring_remove(buffer, &result);
  TEST_ASSERT_EQUAL_INT(3, result);
	
	ring_remove(buffer, &result);
  TEST_ASSERT_EQUAL_INT(4, result);
}

void it_should_not_exceed_its_maximum_nbOfElements(void) {
  ring_add(buffer, 1);
  ring_add(buffer, 2);
  ring_add(buffer, 3);
  ring_add(buffer, 4);
  ring_add(buffer, 5);
  TEST_ASSERT_EQUAL_INT(MAX_nbOfElements, buffer->nbOfElements);
}

void it_should_overwrite_the_oldest_element(void) {
	//add 10 elements
	for (int i=1; i<=10; i++) {
		ring_add(buffer, i);
	}
	int result=0;
	ring_remove(buffer, &result);
  TEST_ASSERT_EQUAL_INT(7, result);

	ring_add(buffer, 11);	//intermediate add

	ring_remove(buffer, &result);
  TEST_ASSERT_EQUAL_INT(8, result);

	ring_add(buffer, 12); //intermediate add

	for (int i=9; i<=12; i++) {	
		ring_remove(buffer, &result);
		TEST_ASSERT_EQUAL_INT(i, result);
	}
}

void it_should_return_false_if_nothing_was_removed(void){
	for (int i=1; i<=4; i++) {
		ring_add(buffer, i);
	}

	int result;
	bool success;
	for (int i=1; i<=4; i++) {	
		success = ring_remove(buffer, &result);
		TEST_ASSERT_EQUAL_INT(i, result);
		TEST_ASSERT_TRUE(success);
	}

	for (int i=1; i<=4; i++) {	
		success = ring_remove(buffer, &result);
		TEST_ASSERT_FALSE(success);
	}
}


int main(void) {
  UnityBegin("RingBuffer");

  RUN_TEST(test_ring_create);
  RUN_TEST(an_empty_ring_should_have_nbOfElements_0);
  RUN_TEST(it_should_report_the_correct_number_of_elements);
  RUN_TEST(it_should_return_the_elements_in_a_fifo_order);
  RUN_TEST(it_should_not_exceed_its_maximum_nbOfElements);
  RUN_TEST(it_should_overwrite_the_oldest_element);
  RUN_TEST(it_should_return_false_if_nothing_was_removed);

  UnityEnd();
  return 0;
}