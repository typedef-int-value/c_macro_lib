/*
 * File:   c_algorithms.h
 * Author: sbkang
 * Distributed under the Boost Software License, Version 1.0.
 */
#pragma once
#include <stdint.h>

#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define ABS(x)      ( ((x)<0)?-(x):(x) )

#define SET_INTERSECTION(IN1PTR, IN1LEN, IN2PTR, IN2LEN, OUTPTR, OUTLEN, OUTCOUNT) \
  do {  \
    uint32_t _length = 0;\
    for (uint32_t _i = 0; _i < IN1LEN; ++_i)  \
      for (uint32_t _j = 0; _j < IN2LEN; ++_j)  \
      { \
        if (IN1PTR[_i] == IN2PTR[_j] ) { \
          OUTPTR[_length++] = IN2PTR[_j]; \
        } \
      } \
      *OUTCOUNT = _length; \
    }  while(0); \
\

