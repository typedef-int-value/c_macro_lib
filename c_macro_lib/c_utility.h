/*
 * File:   c_utility.h
 * Author: sbkang
 * Distributed under the Boost Software License, Version 1.0.
 */

#pragma once
#include <stdint.h>

#define PAIR_CREATE_TYPE(TYPENAME, FIRST, SECOND)                                                                      \
  typedef struct TYPENAME                                                                                              \
  {                                                                                                                    \
    FIRST first;                                                                                                       \
    SECOND second;                                                                                                     \
  } TYPENAME
