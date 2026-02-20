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
Wraps `value` (`int32_t`) to the inclusive range [`min`, `max`] (`int32_t`) using modular arithmetic so that values outside the range are wrapped back within bounds.

### microClamp<T>

```cpp
 T value = microClamp<T>( value, min, max);
```
Clamps `value` to the range [`min`,`max`], returning the clamped result of the same type as the inputs.

### microMap<T>

```cpp
 T value = microMap<T>( value, in_min, in_max, out_min, out_max);
```
Maps `value` from the input range [`in_min`,`in_max`] to the output range [`out_min`,`out_max`] using linear scaling and returns the mapped value of the same type as the inputs.

### microRandomDeterministic32

```cpp
 uint32_t value = microRandomDeterministic32( x);
```
Generates a deterministic pseudo-random value from `x` (`uint32_t`) using a fast hash function and returns the result as `uint32_t`.

### microRandom01

```cpp
 float value = microRandom01( x);
```
Generates a deterministic pseudo-random floating-point value between 0.0 and 1.0 from `x` (`uint32_t`) and returns the result as `float`.

### microRandomInterpolated01

```cpp
 float value = microRandomInterpolated01( x);
```
Generates a deterministic pseudo-random floating-point value between 0.0 and 1.0 from `x` (`float`) by using the integer part of `x` as a seed and linearly interpolating between consecutive integer steps using the fractional part, returning the result as `float`.

### microHashFnv1a

```cpp
 uint32_t value = microHashFnv1a( s);
```
Computes a 32-bit FNV-1a hash of the null-terminated string `s` (`const char *`) and returns the resulting hash as `uint32_t`.


