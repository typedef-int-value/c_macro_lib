# c_macro_lib
c_macro_lib is a simple generic library based on C. I wanted to implement a library in C similar to C++'s vector, stack(or deque). With c_deque, you can use it like a vector for your desired data type. This code target is firmware levels, such as STM32C series.

Currently, the library consists of the following codes:

## consist of files
- c_deque can be used as a replacement for \<vector> and \<stack> and \<deque>.
- c_algorithms.h implements some APIs of \<algorithm>. 
- c_array.h is used to make arrays easier to create.
- c_build_date.h is used to obtain the date of compilation as integer. I mainly use it for version information.
- c_endian.h allows conversions for primitive types.
- c_optional.h is used as a replacement for <optional>.
- c_utility.h is used to implement <utility>. Currently, it can only create std::pair<ty1, ty2>.

## examples
## example of c_deque.h
```c

/* create uint8_t with size 3. */
DEQUE_CREATE_TYPE(u8_deque_type, uint8_t, 3)              // declare header and implementation in c
//DEQUE_CREATE_HEADER(u8_deque_type, uint8_t, 3)          // or declare seperately: for .h file
//DEQUE_CREATE_IMPLEMENTATION(u8_deque_type, uint8_t, 3)  // and implementation: for .c(cpp) file

int main(int argc, char **argv)
{
  uint8_t value = 1;
  u8_deque_type deq = {};
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

  /* deque has 3, 2, 1. */
  uint8_t front_value = 0;
  ec = u8_deque_type_front(&deq, &front_value);
  uint8_t back_value = 0;
  ec = u8_deque_type_back(&deq, &back_value);
  assert(front_value == 3);

  /* deque has 2, 1. */
  u8_deque_type_pop_front(&deq);
  ec = u8_deque_type_front(&deq, &front_value);
  assert(front_value == 2);

  /* deque has 1. */
  u8_deque_type_pop_front(&deq);
  ec = u8_deque_type_front(&deq, &front_value);
  assert(front_value == 1);

  /* deque is empty. */
  u8_deque_type_pop_front(&deq);
  ec = u8_deque_type_front(&deq, &front_value);
  assert(ec == u8_deque_type_ec_data_is_empty);
  assert(front_value == 1);

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
```