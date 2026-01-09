

#ifndef __MICRO_TOF_H__
#define __MICRO_TOF_H__

#include <Arduino.h>
#include <cmath> // for fmodf

#ifndef MICRO_TOF_COUNT_OF_ARRAY
#define MICRO_TOF_COUNT_OF_ARRAY(X) (sizeof(X) / sizeof(X[0]))
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

  int wrapExclusive(int value, int min, int max)
  {
    int range = max - min;
    if (range == 0)
      return min; // avoid division by zero

    int result = (value - min) % range;
    if (result < 0)
      result += range; // ensure positive result

    return result + min;
  }

  // Clamps 'value' to the range [min, max_exclusive-1]
  int32_t clampExclusive(int32_t value, int32_t min, int32_t max)
  {
    if (value <= min)
      return min;
    if (value >= max)
      return max - 1;
    return value;
  }

  // Clamps 'value' to the range [min, max]
  float clampInclusivef(float value, float min, float max)
  {
    if (value <= min)
      return min;
    if (value >= max)
      return max;
    return value;
  }

  float wrapExclusivef(float value, float min, float max)
  {
    float range = max - min;
    if (range == 0.0f)
      return min; // avoid division by zero

    float result = fmodf(value - min, range);
    if (result < 0.0f)
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


  // Simple C-style resizable array template
  template <typename T>
  class ResizableArray
  {
    T *data_ = nullptr;   // pointer to array
    size_t count_ = 0;    // number of elements used
    size_t capacity_ = 4; // allocated size

  public:
    ResizableArray(size_t initialCapacity = 4)
        : capacity_(initialCapacity)
    {
      data_ = (T *)malloc(sizeof(T) * capacity_);
    }

    ~ResizableArray()
    {
      if (data_)
        free(data_);
    }

    size_t getCount() const { return count_; }

    T &operator[](size_t index)
    {
      // no bounds check for speed; optional to add clamp
      return data_[index];
    }

    const T &operator[](size_t index) const
    {
      return data_[index];
    }

    void add(const T &item)
    {
      if (count_ >= capacity_)
      {
        // grow array by 4
        size_t newCapacity = capacity_ + 4;
        T *newData = (T *)malloc(sizeof(T) * newCapacity);
        if (!newData)
          return; // handle allocation failure
        memcpy(newData, data_, sizeof(T) * count_);
        free(data_);
        data_ = newData;
        capacity_ = newCapacity;
      }

      data_[count_++] = item;
    }

    T *raw() { return data_; } // access raw array if needed
  };

}
#endif
