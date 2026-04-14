#pragma once
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "c_macro_lib/c_deque.h"

DEQUE_CREATE_TYPE(u8_deque_type, uint8_t, 3) // declare header and implementation in c
// DEQUE_CREATE_HEADER(u8_deque_type, uint8_t, 3)          // or can declare only header for .h file
// DEQUE_CREATE_IMPLEMENTATION(u8_deque_type, uint8_t, 3)  // and implementation for .c(cpp) file

void print_u8(uint8_t *value)
{
  printf("%d, ", *value);
}

int c_deque_example()
{
  uint8_t value = 1;
  u8_deque_type deq = {0};
  u8_deque_type_ec_t ec = 0;

  int size = u8_deque_type_size(&deq);
  assert(size == 0);
  int max_size = u8_deque_type_max_size(&deq);
  assert(max_size == 3);

  /* deque has 1. */
  value = 1;
  ec = u8_deque_type_push_front(&deq, &value);
  size = u8_deque_type_size(&deq);
  assert(size == 1);

  /* deque has 2, 1, */
  value = 2;
  ec = u8_deque_type_push_front(&deq, &value);
  size = u8_deque_type_size(&deq);
  assert(size == 2);

  /* deque has 3, 2, 1. */
  value = 3;
  ec = u8_deque_type_push_front(&deq, &value);
  size = u8_deque_type_size(&deq);
  assert(size == 3);

  /* deque has 3, 2, 1. because deque max size is 3. */
  value = 4;
  ec = u8_deque_type_push_front(&deq, &value);
  size = u8_deque_type_size(&deq);
  assert(ec == u8_deque_type_ec_data_is_full);
  assert(size == 3);

  /* deque has 4, 3, 2. because deque max size is 3. */
  int overflow = u8_deque_type_push_front_overwrite(&deq, &value);
  size = u8_deque_type_size(&deq);
  assert(size == 3);

  /* deque has 4, 3, 2. */
  uint8_t front_value = 0;
  ec = u8_deque_type_front(&deq, &front_value);
  uint8_t back_value = 0;
  ec = u8_deque_type_back(&deq, &back_value);
  assert(front_value == 4);

  /* deque has 3, 2, 2. because deque max size is 3. */
  value = 2;
  overflow = u8_deque_type_push_back_overwrite(&deq, &value);
  size = u8_deque_type_size(&deq);
  assert(size == 3);

  /* deque has 3, 2, 2. */
  size = u8_deque_type_size(&deq);
  u8_deque_type_back(&deq, &back_value);
  assert(back_value == 2);
  assert(size == 3);
  printf("foreach: ");
  u8_deque_type_for_each(&deq, print_u8);
  printf("\nfor_each_reverse: ");
  u8_deque_type_for_each_reverse(&deq, print_u8);
  uint8_t *at_value = u8_deque_type_at(&deq, 0);

  /* deque has 3, 2. */
  u8_deque_type_pop_back(&deq);
  size = u8_deque_type_size(&deq);
  ec = u8_deque_type_back(&deq, &back_value);
  ec = u8_deque_type_front(&deq, &front_value);
  assert(back_value == 2);
  assert(front_value == 3);
  assert(size == 2);

  /* deque has 2. */
  u8_deque_type_pop_front(&deq);
  size = u8_deque_type_size(&deq);
  ec = u8_deque_type_back(&deq, &back_value);
  ec = u8_deque_type_front(&deq, &front_value);
  assert(back_value == 2);
  assert(front_value == 2);
  assert(size == 1);

  /* deque has empty. */
  u8_deque_type_pop_front(&deq);
  ec = u8_deque_type_front(&deq, &front_value);
  assert(ec == u8_deque_type_ec_data_is_empty);

  /* deque is empty. front_value keep 2. */
  u8_deque_type_pop_front(&deq);
  ec = u8_deque_type_front(&deq, &front_value);
  assert(ec == u8_deque_type_ec_data_is_empty);
  assert(front_value == 2);

  /* deque is empty. */
  u8_deque_type_pop_front(&deq);
  ec = u8_deque_type_front(&deq, &front_value);
  assert(ec == u8_deque_type_ec_data_is_empty);

  /* deque has 4. */
  value = 4;
  ec = u8_deque_type_push_back(&deq, &value);
  size = u8_deque_type_size(&deq);
  assert(size == 1);

  /* deque has 4, 5. */
  value = 5;
  ec = u8_deque_type_push_back(&deq, &value);
  size = u8_deque_type_size(&deq);
  assert(size == 2);

  /* deque has 4, 5. */
  ec = u8_deque_type_front(&deq, &front_value);
  assert(front_value == 4);
  ec = u8_deque_type_back(&deq, &back_value);
  assert(back_value == 5);

  /* deque has 5. */
  u8_deque_type_pop_front(&deq);
  size = u8_deque_type_size(&deq);
  ec = u8_deque_type_front(&deq, &front_value);
  ec = u8_deque_type_back(&deq, &back_value);
  assert(size == 1);
  assert(front_value == 5);
  assert(back_value == 5);
  assert(ec == u8_deque_type_ec_success);

  return (0);
}
