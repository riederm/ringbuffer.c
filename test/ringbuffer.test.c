#include "vendor/unity.h"
#include "../src/ringbuffer.h"
#include <stdlib.h>


const int MAX_SIZE = 4 ;
RingBuffer* buffer;

void setUp(void) {
    buffer = ring_create(MAX_SIZE);
}

void tearDown(void) {
    ring_delete(buffer);
}

void test_ring_create(void)
{
  TEST_ASSERT_NOT_NULL(buffer);
  for (int i = 0; i < MAX_SIZE; i++) {
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, buffer->data[i], "data should be 0");
  }
}

void test_empty_ring_should_have_size_0(void)
{
  int size = buffer->size;
  TEST_ASSERT_EQUAL_INT(0, size);
}

void test_should_report_number_of_elements(void)
{
    ring_add(buffer,1);
    ring_add(buffer,2);
    ring_add(buffer,3);
    TEST_ASSERT_EQUAL_INT(3, buffer->size);
}

void test_should_not_exceed_its_maximum_size(void)
{
    ring_add(buffer,1);
    ring_add(buffer,2);
    ring_add(buffer,3);
    ring_add(buffer,4);
    ring_add(buffer,5);
    TEST_ASSERT_EQUAL_INT(MAX_SIZE, buffer->size);
}


void test_elements_are_added(void)
{
    ring_add(buffer,1);
    ring_add(buffer,2);
    ring_add(buffer,3);
    ring_add(buffer,4);

    TEST_ASSERT_EQUAL_INT(1, buffer->data[0]);
    TEST_ASSERT_EQUAL_INT(2, buffer->data[1]);
    TEST_ASSERT_EQUAL_INT(3, buffer->data[2]);
    TEST_ASSERT_EQUAL_INT(4, buffer->data[3]);
}


void test_on_empty_returns_false(void)
{
    int result;
    TEST_ASSERT_EQUAL_INT(false, ring_remove(buffer,&result));
   
}

void test_remove_returns_oldest_element(void)
{
    ring_add(buffer,1);
    ring_add(buffer,2);
    ring_add(buffer,3);
    ring_add(buffer,4);

    int result;

    TEST_ASSERT_EQUAL_INT(true, ring_remove(buffer,&result));
    TEST_ASSERT_EQUAL_INT(1, result);

    TEST_ASSERT_EQUAL_INT(true, ring_remove(buffer,&result));
    TEST_ASSERT_EQUAL_INT(2, result);

    TEST_ASSERT_EQUAL_INT(true, ring_remove(buffer,&result));
    TEST_ASSERT_EQUAL_INT(3, result);

    TEST_ASSERT_EQUAL_INT(true, ring_remove(buffer,&result));
    TEST_ASSERT_EQUAL_INT(4, result);
   
    TEST_ASSERT_EQUAL_INT(0,buffer->size);

}

void test_write_around_the_clock(void)
{
    //make buffer full  
    ring_add(buffer,1);
    ring_add(buffer,2);
    ring_add(buffer,3);
    ring_add(buffer,4);

    //buffer is full now next add should wirte to first position
    ring_add(buffer,5);
    ring_add(buffer,6);

    TEST_ASSERT_EQUAL_INT(5,buffer->data[0]);
    TEST_ASSERT_EQUAL_INT(6,buffer->data[1]);
}

void test_write_around_the_clock_remove(void)
{
    //make buffer full  
    ring_add(buffer,1);
    ring_add(buffer,2);
    ring_add(buffer,3);
    ring_add(buffer,4);

    //buffer is full now next add should wirte to first position
    ring_add(buffer,5);
    ring_add(buffer,6);

    int result;
    bool success = ring_remove(buffer,&result);
    TEST_ASSERT_EQUAL_INT(3,result);

    ring_remove(buffer,&result);
    TEST_ASSERT_EQUAL_INT(4,result);
}

void test_delete_sets_pointer_to_null(void)
{
   ring_delete(buffer);
    
}


int main(void)
{
   UnityBegin("RingBuffer");

   RUN_TEST(test_ring_create);
   RUN_TEST(test_empty_ring_should_have_size_0);
   RUN_TEST(test_should_report_number_of_elements);
   RUN_TEST(test_should_not_exceed_its_maximum_size);
   RUN_TEST(test_elements_are_added);
   RUN_TEST(test_on_empty_returns_false);
   RUN_TEST(test_remove_returns_oldest_element);
   RUN_TEST(test_write_around_the_clock);
   RUN_TEST(test_write_around_the_clock_remove);
   RUN_TEST(test_delete_sets_pointer_to_null);
   UnityEnd();
   return 0;
}