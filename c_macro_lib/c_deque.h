/*
 * File:   c_deque.h
 * Author: sbkang
 * Distributed under the Boost Software License, Version 1.0.
 */
#pragma once

#define DEQUE_CREATE_HEADER(TYPENAME, TYPE, MAXSIZE)                                                                   \
  typedef enum                                                                                                         \
  {                                                                                                                    \
    TYPENAME##_ec_success = 0,                                                                                         \
    TYPENAME##_ec_data_is_full,                                                                                        \
    TYPENAME##_ec_data_is_empty                                                                                        \
  } TYPENAME##_ec_t;                                                                                                   \
                                                                                                                       \
  typedef struct                                                                                                       \
  {                                                                                                                    \
    TYPE data_[MAXSIZE + 1];                                                                                           \
    int _head;                                                                                                         \
    int _tail;                                                                                                         \
  } TYPENAME;                                                                                                          \
                                                                                                                       \
  int TYPENAME##_internal_prev_pos(int pos);                                                                           \
  int TYPENAME##_internal_next_pos(int pos);                                                                           \
  TYPENAME##_ec_t TYPENAME##_front(TYPENAME *deque, TYPE *data);                                                       \
  TYPENAME##_ec_t TYPENAME##_back(TYPENAME *deque, TYPE *data);                                                        \
  void TYPENAME##_pop_front(TYPENAME *deque);                                                                          \
  void TYPENAME##_pop_back(TYPENAME *deque);                                                                           \
  TYPENAME##_ec_t TYPENAME##_push_back(TYPENAME *deque, TYPE *data);                                                   \
  TYPENAME##_ec_t TYPENAME##_push_front(TYPENAME *deque, TYPE *data);                                                  \
  void TYPENAME##_clear(TYPENAME *deque);                                                                              \
  int TYPENAME##_size(TYPENAME *deque);                                                                                \
  int TYPENAME##_max_size(TYPENAME *deque);

#define DEQUE_CREATE_IMPLEMENTATION(TYPENAME, TYPE, MAXSIZE)                                                           \
  int TYPENAME##_internal_prev_pos(int pos)                                                                            \
  {                                                                                                                    \
    return (pos + MAXSIZE + 1 - 1) % (MAXSIZE + 1);                                                                    \
  }                                                                                                                    \
  int TYPENAME##_internal_next_pos(int pos)                                                                            \
  {                                                                                                                    \
    return (pos + 1) % (MAXSIZE + 1);                                                                                  \
  }                                                                                                                    \
  TYPENAME##_ec_t TYPENAME##_front(TYPENAME *deque, TYPE *data)                                                        \
  {                                                                                                                    \
    if (deque->_head == deque->_tail)                                                                                  \
      return TYPENAME##_ec_data_is_empty;                                                                              \
    *data = deque->data_[deque->_head];                                                                                \
                                                                                                                       \
    return TYPENAME##_ec_success;                                                                                      \
  }                                                                                                                    \
  TYPENAME##_ec_t TYPENAME##_back(TYPENAME *deque, TYPE *data)                                                         \
  {                                                                                                                    \
    if (deque->_head == deque->_tail)                                                                                  \
      return TYPENAME##_ec_data_is_empty;                                                                              \
    *data = deque->data_[TYPENAME##_internal_prev_pos(deque->_tail)];                                                  \
                                                                                                                       \
    return TYPENAME##_ec_success;                                                                                      \
  }                                                                                                                    \
  void TYPENAME##_pop_front(TYPENAME *deque)                                                                           \
  {                                                                                                                    \
    if (deque->_head == deque->_tail)                                                                                  \
      return;                                                                                                          \
    deque->_head = TYPENAME##_internal_next_pos(deque->_head);                                                         \
  }                                                                                                                    \
  void TYPENAME##_pop_back(TYPENAME *deque)                                                                            \
  {                                                                                                                    \
    if (deque->_head == deque->_tail)                                                                                  \
      return;                                                                                                          \
    deque->_tail = TYPENAME##_internal_prev_pos(deque->_tail);                                                         \
  }                                                                                                                    \
  TYPENAME##_ec_t TYPENAME##_push_back(TYPENAME *deque, TYPE *data)                                                    \
  {                                                                                                                    \
    if (deque->_head == TYPENAME##_internal_next_pos(deque->_tail))                                                    \
    {                                                                                                                  \
      return TYPENAME##_ec_data_is_full;                                                                               \
    }                                                                                                                  \
                                                                                                                       \
    deque->data_[deque->_tail] = *data;                                                                                \
    deque->_tail = TYPENAME##_internal_next_pos(deque->_tail);                                                         \
                                                                                                                       \
    return TYPENAME##_ec_success;                                                                                      \
  }                                                                                                                    \
  TYPENAME##_ec_t TYPENAME##_push_front(TYPENAME *deque, TYPE *data)                                                   \
  {                                                                                                                    \
    if (deque->_head == TYPENAME##_internal_next_pos(deque->_tail))                                                    \
    {                                                                                                                  \
      return TYPENAME##_ec_data_is_full;                                                                               \
    }                                                                                                                  \
    deque->_head = TYPENAME##_internal_prev_pos(deque->_head);                                                         \
    deque->data_[deque->_head] = *data;                                                                                \
                                                                                                                       \
    return TYPENAME##_ec_success;                                                                                      \
  }                                                                                                                    \
  void TYPENAME##_clear(TYPENAME *deque)                                                                               \
  {                                                                                                                    \
    deque->_tail = deque->_head = 0;                                                                                   \
  }                                                                                                                    \
  int TYPENAME##_size(TYPENAME *deque)                                                                                 \
  {                                                                                                                    \
    if (deque->_head == deque->_tail)                                                                                  \
    {                                                                                                                  \
      return 0;                                                                                                        \
    }                                                                                                                  \
    else if (deque->_tail > deque->_head)                                                                              \
    {                                                                                                                  \
      return (deque->_tail - deque->_head);                                                                            \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
      return (deque->_tail + MAXSIZE - deque->_head + 1);                                                              \
    }                                                                                                                  \
  }                                                                                                                    \
  int TYPENAME##_max_size(TYPENAME *deque)                                                                             \
  {                                                                                                                    \
    return ((sizeof(deque->data_) - sizeof(deque->data_[0])) / sizeof(deque->data_[0]));                               \
  }

#define DEQUE_CREATE_TYPE(TYPENAME, TYPE, MAXSIZE)                                                                     \
  DEQUE_CREATE_HEADER(TYPENAME, TYPE, MAXSIZE)                                                                         \
  DEQUE_CREATE_IMPLEMENTATION(TYPENAME, TYPE, MAXSIZE)\
