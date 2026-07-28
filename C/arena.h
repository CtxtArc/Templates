/* arena.h - v1.1 - Single-file arena allocator en C99
 *
 * ============================================================================
 * UTILISATION
 * ============================================================================
 *
 * Dans UN SEUL fichier C :
 *
 * #define ARENA_IMPLEMENTATION
 * #include "arena.h"
 *
 * Les autres fichiers :
 *
 * #include "arena.h"
 *
 * ============================================================================
 */

#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>
#include <stdint.h>

/*
 * STB-style :
 * - extern pendant les includes normaux
 * - définition pendant ARENA_IMPLEMENTATION
 */
#ifndef ARENA_DEF
#ifdef ARENA_IMPLEMENTATION
#define ARENA_DEF
#else
#define ARENA_DEF extern
#endif
#endif

// ============================================================================
// MACROS UTILITAIRES
// ============================================================================

#define arena_push(arena_ptr, type)                                            \
  ((type *)arena_zalloc((arena_ptr), sizeof(type)))

#define arena_push_array(arena_ptr, type, count)                               \
  ((type *)arena_zalloc((arena_ptr), sizeof(type) * (count)))

// ============================================================================
// STRUCTURES
// ============================================================================

typedef struct ArenaBlock {

  size_t capacity;
  size_t offset;

  struct ArenaBlock *next;

  uint8_t data[];

} ArenaBlock;

typedef struct {

  ArenaBlock *head;
  ArenaBlock *current;

  size_t chunk_size;

} Arena;

// ============================================================================
// API
// ============================================================================

ARENA_DEF Arena arena_create(size_t default_capacity);

ARENA_DEF void *arena_alloc(Arena *arena, size_t size);

ARENA_DEF void *arena_zalloc(Arena *arena, size_t size);

ARENA_DEF char *arena_strdup(Arena *arena, const char *str);

ARENA_DEF void arena_reset(Arena *arena);

ARENA_DEF void arena_destroy(Arena *arena);

#endif /* ARENA_H */

// ============================================================================
// IMPLEMENTATION
// ============================================================================

#ifdef ARENA_IMPLEMENTATION

#ifndef ARENA_IMPLEMENTED
#define ARENA_IMPLEMENTED

#include <stdlib.h>
#include <string.h>

#ifndef ARENA_MALLOC
#define ARENA_MALLOC(size) malloc(size)
#define ARENA_FREE(ptr) free(ptr)
#endif

#ifndef ARENA_ALIGNMENT
#define ARENA_ALIGNMENT 16
#endif

#define ARENA_ALIGN_UP(n, a) (((n) + (a) - 1) & ~((a) - 1))

static ArenaBlock *arena__block_create(size_t capacity) {
  ArenaBlock *block = ARENA_MALLOC(sizeof(ArenaBlock) + capacity);

  if (!block)
    return NULL;

  block->capacity = capacity;
  block->offset = 0;
  block->next = NULL;

  return block;
}

ARENA_DEF Arena arena_create(size_t default_capacity) {

  Arena arena = {0};

  arena.chunk_size = default_capacity;

  ArenaBlock *block = arena__block_create(default_capacity);

  arena.head = block;
  arena.current = block;

  return arena;
}

ARENA_DEF void *arena_alloc(Arena *arena, size_t size) {

  if (!arena || !arena->current)
    return NULL;

  size_t aligned_size = ARENA_ALIGN_UP(size, ARENA_ALIGNMENT);

  ArenaBlock *block = arena->current;

  if (block->offset + aligned_size > block->capacity) {

    size_t capacity = arena->chunk_size;

    if (aligned_size > capacity)
      capacity = aligned_size;

    ArenaBlock *new_block = arena__block_create(capacity);

    if (!new_block)
      return NULL;

    block->next = new_block;

    arena->current = new_block;

    block = new_block;
  }

  void *ptr = &block->data[block->offset];

  block->offset += aligned_size;

  return ptr;
}

ARENA_DEF void *arena_zalloc(Arena *arena, size_t size) {

  void *ptr = arena_alloc(arena, size);

  if (ptr)
    memset(ptr, 0, size);

  return ptr;
}

ARENA_DEF char *arena_strdup(Arena *arena, const char *str) {

  if (!str)
    return NULL;

  size_t len = strlen(str) + 1;

  char *dup = arena_alloc(arena, len);

  if (dup)
    memcpy(dup, str, len);

  return dup;
}

ARENA_DEF void arena_reset(Arena *arena) {

  if (!arena)
    return;

  ArenaBlock *block = arena->head;

  while (block) {

    block->offset = 0;

    block = block->next;
  }

  arena->current = arena->head;
}

ARENA_DEF void arena_destroy(Arena *arena) {

  if (!arena)
    return;

  ArenaBlock *block = arena->head;

  while (block) {

    ArenaBlock *next = block->next;

    ARENA_FREE(block);

    block = next;
  }

  arena->head = NULL;

  arena->current = NULL;
}

#endif /* ARENA_IMPLEMENTED */

#endif /* ARENA_IMPLEMENTATION */
