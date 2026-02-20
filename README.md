# MicroCommon

Utility library for Arduino Micro Libraries

Git URL : https://github.com/thomasfredericks/MicroCommon

Namespace: global

## Functions

### microModulo

```cpp
 int32_t value = microModulo( value, modulus);
```
Returns `value` (`int32_t`) modulo `modulus` (`int32_t`), ensuring the result is always non-negative even if `value` is negative.

### microWrap

```cpp
 int32_t value = microWrap( value, min, max);
```
Wraps `value` (`int32_t`) to the range [`min` (`int32_t`), `max` (`int32_t`)], inclusive of `max`, using modular arithmetic.

### microClamp<T>

```cpp
 T value = microClamp<T>( value, min, max);
```
Clamps `value` (`T`) to the range [`min` (`T`), `max` (`T`)], returning `max` (`T`) if `value` exceeds it and `value` itself otherwise.

### microMap<T>

```cpp
 T value = microMap<T>( value, in_min, in_max, out_min, out_max);
```
Maps `value` (`T`) from the input range [`in_min` (`T`), `in_max` (`T`)] to the output range [`out_min` (`T`), `out_max` (`T`)], linearly scaling the value.

### microRandomDeterministic32

```cpp
 uint32_t value = microRandomDeterministic32( x);
```
Generates a deterministic pseudo-random `uint32_t` value from input `x` (`uint32_t`) using a fast hash function.

### microRandom01

```cpp
 float value = microRandom01( x);
```
Generates a deterministic pseudo-random `float` between 0.0 and 1.0 from input `x` (`uint32_t`) using a fast hash function.

### microRandomInterpolated01

```cpp
 float value = microRandomInterpolated01( x);
```
Generates a deterministic pseudo-random `float` between 0.0 and 1.0 for `x` (`float`) by using the integer part of `x` as a seed and linearly interpolating between `x` and `x+1` using the fractional part.

### microHashFnv1a

```cpp
 uint32_t value = microHashFnv1a( s);
```
Computes a 32-bit FNV-1a hash of the null-terminated string `s` (`const char *`), returning the hash as `uint32_t`.


