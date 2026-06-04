#ifndef STD_H
#define STD_H

// Required standard libraries for base types
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// --- Unsigned Integers ---
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef size_t   usize;

// --- Signed Integers ---
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef intptr_t isize;

// --- Floating Point ---
typedef float  f32;
typedef double f64;

// --- Math & Logic Macros ---
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

// Aligns 'n' UP to the nearest multiple of 'p' (p MUST be a power of 2)
#define ALIGN_UP_POW2(n, p) (((n) + (p) - 1) & ~((p) - 1))

// Aligns 'n' DOWN to the nearest multiple of 'p' (p MUST be a power of 2)
#define ALIGN_DOWN_POW2(n, p) ((n) & ~((p) - 1))

// --- Memory Size Helpers ---
#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)
#define TiB(n) ((u64)(n) << 40) 

// --- Array Helpers ---
#define LEN(x) (sizeof(x) / sizeof((x)[0]))

#endif // !STD_H
