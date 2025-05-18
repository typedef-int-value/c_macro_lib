/*
 * File:   c_array.h
 * Author: sbkang
 * Distributed under the Boost Software License, Version 1.0.
 */

#pragma once
#include <stdint.h>

#define ARRAY(TYPE, MAX_SIZE) TYPE##_array_##MAX_SIZE##_type

#define ARRAY_CREATE_TYPE(TYPENAME, TYPE, MAX_SIZE)                                                                    \
  typedef struct TYPENAME                                                                                              \
  {                                                                                                                    \
    TYPE data[MAX_SIZE];                                                                                               \
    uint32_t _size;                                                                                                    \
  } TYPENAME

#define ARRAY_PUT(ARRAY, DATA)                                                                                         \
  {                                                                                                                    \
    ARRAY.data[ARRAY._size++] = DATA;                                                                                  \
  }

#define ARRAY_SIZE (ARRAY_DATA)(ARRAY_DATA._size)
