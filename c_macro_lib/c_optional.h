/*
 * File:   c_optional.h
 * Author: sbkang
 * Distributed under the Boost Software License, Version 1.0.
 */

#pragma once
#include <stdint.h>

#define OPTIONAL_CREATE_TYPE(TYPENAME, TYPE) \
  typedef struct TYPENAME {        \
    TYPE data;                     \
    boolean _has_value;            \
  } TYPENAME

#define OPTIONAL_SET(OPTIONAL_DATA, DATA) \
  {                                       \
    OPTIONAL_DATA.data = DATA;            \
    OPTIONAL_DATA._has_value = 1;         \
  }

#define OPTIONAL_HAS_VALUE (OPTIONAL_DATA)(OPTIONAL_DATA._has_value)  \

#define PAIR_CREATE_TYPE(TYPENAME, FIRST, SECOND) \
  typedef struct TYPENAME {                       \
    FIRST first;                                  \
    SECOND second;                                \
  } TYPENAME      \


