

#ifndef __MICRO_COMMON_H__
#define __MICRO_COMMON_H__

#include <Arduino.h>

constexpr int32_t microModulo(int32_t value, int32_t modulus)
{
  return (value % modulus + modulus) % modulus;
}

// Wrap 'value' to the range [min, max] (max inclusive)
constexpr int32_t microWrap(int32_t value, int32_t min, int32_t max)
{
  return microModulo(value - min, max - min + 1) + min;
}

// Clamps 'value' to the range [min, max] (max inclusive)
template <typename T>
constexpr T microClamp(T value, T min, T max)
{
    return (value >= max ? max : value);
}

// Maps 'value' from [in_min, in_max] to [out_min, out_max]
template <typename T>
constexpr T microMap(T value, T in_min, T in_max, T out_min, T out_max)
{
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// ==============================================

// Deterministic random (fast hash)
uint32_t microRandomDeterministic32(uint32_t x)
{
  x ^= x >> 17;
  x *= 0xed5ad4bbU;
  x ^= x >> 11;
  x *= 0xac4c1b51U;
  x ^= x >> 15;
  x *= 0x31848babU;
  x ^= x >> 14;
  return x;
}

// ==============================================

// Random float between 0.0 and 1.0
float microRandom01(uint32_t x)
{
  return microRandomDeterministic32(x) / 4294967295.0f;
}

// Deterministic random (fast hash) with interpolation between integer steps.
// Uses the integer part of x as a seed and linearly interpolates
// between x and x+1 using the fractional part of x.
float microRandomInterpolated01(float x)
{
  int xi = floor(x);
  float xf = x - xi;
  float a = microRandom01(xi);
  float b = microRandom01(xi + 1);
  return a * (1 - xf) + b * xf;
}

// FNV-1a hash for strings
uint32_t microHashFnv1a(const char *s)
{
  uint32_t hash = 2166136261u;
  while (*s)
  {
    hash ^= (uint8_t)*s++;
    hash *= 16777619u;
  }
  return hash;
}

#endif
