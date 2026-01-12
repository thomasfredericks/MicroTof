# MicroCommon

Utility library for Arduino Micro Libraries

Git URL : https://github.com/thomasfredericks/MicroCommon

Namespace: `Micro`


## Functions

### `Micro::modulo(value, modulus)`

Computes the modulo of a value, ensuring a non-negative result.

- **Parameters:**
  - `value` – The input value (int32_t).
  - `modulus` – The modulus to apply (int32_t).
- **Returns:** Non-negative remainder of `value % modulus` (int32_t).



### `Micro::wrap(value, min, max)`

Wraps an integer value into the inclusive range `[min, max]`.

- **Parameters:**
  - `value` – The value to wrap (int32_t).
  - `min` – The minimum bound of the range (int32_t).
  - `max` – The maximum bound of the range (inclusive) (int32_t).
- **Returns:** Wrapped value within `[min, max]` (int32_t).



### `Micro::clamp<T>(value, min, max)`

Clamps a value to lie within the inclusive range `[min, max]`.

- **Parameters:**
  - `value` – The value to clamp (any numeric type T).
  - `min` – The minimum bound (T).
  - `max` – The maximum bound (T).
- **Returns:** Clamped value (T).



### `Micro::map<T>(value, in_min, in_max, out_min, out_max)`

Linearly maps a value from one range to another.

- **Parameters:**
  - `value` – The input value (T).
  - `in_min` – Lower bound of input range (T).
  - `in_max` – Upper bound of input range (T).
  - `out_min` – Lower bound of output range (T).
  - `out_max` – Upper bound of output range (T).
- **Returns:** Value mapped to the output range (T).



### `Micro::randomHash32(x)`

Generates a deterministic 32-bit pseudo-random number from a seed.

- **Parameters:**
  - `x` – Seed value (uint32_t).
- **Returns:** Pseudo-random 32-bit number (uint32_t).


### `Micro::rand01(x)`

Generates a pseudo-random float in `[0.0, 1.0]` from an integer seed.

- **Parameters:**
  - `x` – Seed value (uint32_t).
- **Returns:** Pseudo-random number in `[0.0, 1.0]` (float).


### `Micro::interpolatedRandom01(x)`

Generates a deterministic pseudo-random float in `[0.0, 1.0]` with linear interpolation between integer inputs. Integer part is the random seed for the first random value. Fractional part is the interpolation with the next random value.

- **Parameters:**
  - `x` – Input value (float).
- **Returns:** Interpolated pseudo-random number (float).



## Classes and Structs

### `Micro::Bind<T>`

Holds a key-pointer pair.

- **Template Parameter:** `T` – Pointer type.
- **Description:** Stores a key string and a pointer of type `T`.
- **Members:**
  - `key_` – Key string (const char*).
  - `pointer_` – Stored pointer (T*).
- **Constructors:**
  - `Bind(key, pointer)` – Initializes the pair with a key (const char*) and pointer (T*).
  - `Bind()` – Default constructor.

### `Micro::Binder<T>`

Stores a collection of `[key, pointer]` pairs and provides access.

- **Template Parameter:** `T` – Pointer type.
- **Description:** Maintains an array of `Micro::Bind<T>` pairs and allows retrieval by key or index.
- **Members:**
  - `count_` – Number of stored pairs (size_t).
  - `pairs_` – Pointer to array of pairs (Bind<T>*).
- **Constructors:**
  - `Binder(pairs, count)` – Initializes with array of pairs (Bind<T>*) and count (size_t).
- **Methods:**
  - `get(key)` – Returns pointer associated with the key (T*) or nullptr if not found.  
    - **Parameters:** `key` – Key string (const char*).  
    - **Returns:** Pointer (T*).
  - `get(index)` – Returns pointer at given index or nullptr if out of bounds.  
    - **Parameters:** `index` – Index of pair (size_t).  
    - **Returns:** Pointer (T*).
  - `getCount()` – Returns number of stored pairs.  
    - **Returns:** Count (size_t).
