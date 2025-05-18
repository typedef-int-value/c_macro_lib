/*
 * File:   c_endian.h
 * Author: sbkang
 * Distributed under the Boost Software License, Version 1.0.
 */

#pragma once
#include <limits.h>
#include <stdint.h>
#include <string.h>

#if CHAR_BIT != 8
#error "unsupported char size"
#endif

enum
{
  O32_LITTLE_ENDIAN = 0x03020100ul,
  O32_BIG_ENDIAN = 0x00010203ul,
  O32_PDP_ENDIAN = 0x01000302ul, /* DEC PDP-11 (aka ENDIAN_LITTLE_WORD) */
  O32_HONEYWELL_ENDIAN = 0x02030001ul /* Honeywell 316 (aka ENDIAN_BIG_WORD) */
};

static const union
{
  unsigned char bytes[4];
  uint32_t value;
} o32_host_order = { { 0, 1, 2, 3 } };

#define O32_HOST_ORDER (o32_host_order.value)

inline static uint8_t is_little_endian()
{
  if (O32_HOST_ORDER == O32_LITTLE_ENDIAN)
  {
    return 1;
  }

  return 0;
}

/**********************************************************************************************************************
 *  POD CONVERSION FUNCTION
 *********************************************************************************************************************/

#define BIT(VALUE, POS) ((VALUE & (1 << POS)) >> POS)
#define BIT_VALUE(VAR,POS) (VAR & (1 << POS))
#define BIT_SET(VAR,POS) (VAR |= (1 << POS))
#define BIT_CLEAR(VAR,POS) (VAR &= ((1 << POS)^255))

#define BYTES_TO_16(BYTE1, BYTE2) \
  ((BYTE1) | (BYTE2 << 8u))

#define BYTES_TO_32(BYTE1, BYTE2, BYTE3, BYTE4) \
  ((BYTE1) | (BYTE2 << 8u) | (BYTE3 << 16u) | (BYTE4 << 24u))

inline static void endian_reverse(void *in, void *out, uint8_t size)
{
  uint8_t *p = out;
  uint8_t *inptr = in;

  for (int8_t i = (size - 1); i >= 0; --i)
  {
    *p++ = inptr[i];
  }
}
inline static uint8_t pod_to_bytes(void *in, uint8_t *out, uint8_t size)
{
  memcpy(out, in, size);
  return size;
}
inline static uint8_t bytes_to_pod(uint8_t *in, void *out, uint8_t size)
{
  memcpy(out, in, size);
  return size;
}
inline static uint8_t bytes_to_pod_endian_reverse(uint8_t *in, void *out, uint8_t size)
{
  endian_reverse(in, out, size);
  return size;
}
inline static uint8_t bytes_to_pod_ntoh(uint8_t *in, void *out, uint8_t size)
{
  if (is_little_endian())
  {
    return bytes_to_pod_endian_reverse(in, out, size);
  }
  else
  {
    return bytes_to_pod(in, out, size);
  }
}

/**********************************************************************************************************************
 *  ENDIAN CONVERSION FUNCTION
 *********************************************************************************************************************/

//! Byte swap unsigned short
inline static uint16_t swap_uint16(uint16_t val)
{
  val = (val << 8) | (val >> 8);
  return val;
}

//! Byte swap short
inline static int16_t swap_int16(int16_t val)
{
  return (val << 8) | ((val >> 8) & 0xFF);
}

//! Byte swap unsigned int
inline static uint32_t swap_uint32(uint32_t val)
{
  val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
  return (val << 16) | (val >> 16);
}

//! Byte swap int
inline static int32_t swap_int32(int32_t val)
{
  val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
  return (val << 16) | ((val >> 16) & 0xFFFF);
}

inline static int64_t swap_int64(int64_t val)
{
  val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
  val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
  return (val << 32) | ((val >> 32) & 0xFFFFFFFFULL);
}

inline static uint64_t swap_uint64(uint64_t val)
{
  val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
  val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
  return (val << 32) | (val >> 32);
}