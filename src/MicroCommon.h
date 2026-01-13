

#ifndef __MICRO_COMMON_H__
#define __MICRO_COMMON_H__

#include <Arduino.h>
/* #include <cmath> // for fmodf
#include <type_traits>
#include <assert.h>
#include <cassert>
#include <cstring> */

namespace Micro
{

  int32_t modulo(int32_t value, int32_t modulus)
  {
    return (value % modulus + modulus) % modulus;
  }

  // Wrap 'value' to the range [min, max] (max inclusive)
  int32_t wrap(int32_t value, int32_t min, int32_t max)
  {
    int32_t range = max - min + 1; // +1 for max-inclusive
    if (range <= 1)
      return min;

    return Micro::modulo(value - min, range) + min;
  }

  // Clamps 'value' to the range [min, max] (max inclusive)
  template <typename T>
  T clamp(T value, T min, T max)
  {
    if (value <= min)
      return min;
    if (value >= max)
      return max;
    return value;
  }

  // Maps 'value' from [in_min, in_max] to [out_min, out_max]
  template <typename T>
  T map(T value, T in_min, T in_max, T out_min, T out_max)
  {
    const T run = in_max - in_min;
    if (run == 0)
    {
      return 0;
    }
    const T rise = out_max - out_min;
    const T delta = value - in_min;
    return (delta * rise) / run + out_min;
  }

  // ==============================================

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

  // ==============================================

  // Random float between 0.0 and 1.0
  float rand01(uint32_t x)
  {
    return randomHash32(x) / 4294967295.0f;
  }

  // Deterministic random (fast hash) with interpolation between integer steps.
  // Uses the integer part of x as a seed and linearly interpolates
  // between x and x+1 using the fractional part of x.
  float interpolatedRandom01(float x)
  {
    int xi = floor(x);
    float xf = x - xi;
    float a = rand01(xi);
    float b = rand01(xi + 1);
    return a * (1 - xf) + b * xf;
  }

  // ==============================================

  // Binds a [key, pointer] pair
  template <typename T>
  struct Bind
  {
    // static_assert(std::is_pointer<T>::value, "Bind<T>: T must be a pointer type");

    const char *key_ = nullptr;
    T pointer_ = nullptr;

    Bind(const char *key, T pointer) : key_(key), pointer_(pointer) {};

    Bind() {};
  };

  // ==============================================

  // Collection of [key, pointer] pairs
  template <typename T>
  class Binder
  {
    // static_assert(std::is_pointer<T>::value, "Binder<T>: T must be a pointer type");
    size_t count_ = 0;
    Bind<T> *pairs_;

  public:
    Binder(Bind<T> *pairs, size_t count)
        : pairs_(pairs), count_(count) {

          };

    // get pointer to the stored value by key
    T getPointer(const char *key)
    {
      for (size_t i = 0; i < count_; ++i)
      {
        if (strcmp(pairs_[i].key_, key) == 0)
          return pairs_[i].pointer_;
      }
      return nullptr;
    }

    // get pointer by index
    T getPointer(size_t index)
    {
      if (index >= count_)
        return nullptr;
      return pairs_[index].pointer_;
    }
    
    // get pointer by index
    const char * getKey(size_t index) {
      if (index >= count_)
        return nullptr;
      return pairs_[index].key_;
    }

    size_t getCount() const { return count_; }
  };

} // namespace MicroCommon
#endif
