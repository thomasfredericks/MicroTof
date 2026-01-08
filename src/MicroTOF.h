

#ifndef __MICRO_TOF_H__
#define __MICRO_TOF_H__

#include <Arduino.h>

#ifndef MICRO_TOF_COUNT_OF_ARRAY
#define MICRO_TOF_COUNT_OF_ARRAY(X)  (sizeof(X) / sizeof(X[0]))
#endif

namespace MicroTof
{

  float mapf(float x, float in_min, float in_max, float out_min, float out_max)
  {
    const float run = in_max - in_min;
    if (run == 0)
    {
      // log_e("map(): Invalid input range, min == max");
      return 0;
    }
    const float rise = out_max - out_min;
    const float delta = x - in_min;
    return (delta * rise) / run + out_min;
  }
  
  int wrap(int value, int min, int max_exclusive)
  {
    int range = max_exclusive - min;
    if (range == 0)
      return min; // avoid division by zero

    int result = (value - min) % range;
    if (result < 0)
      result += range; // ensure positive result

    return result + min;
  }

  // Deterministic random (fast hash)
  uint32_t randomHash32(uint32_t x)
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

  float rand01(uint32_t x)
  {
    return randomHash32(x) / 4294967295.0f;
  }

  // Smooth random between integer steps (interpolated hash)
  // The integer part of x is the actual random value
  // The float part is the interpolation factor (% between two random values)
  float interpolatedRandom01(float x, uint32_t seed)
  {
    int xi = floor(x);
    float xf = x - xi;
    float a = rand01(seed + xi);
    float b = rand01(seed + xi + 1);
    return a * (1 - xf) + b * xf;
  }
}
#endif