/* Canonical exported wrappers around the static-inline arena/intern functions
 * in slop_runtime.h. Those are `static inline` (no external symbol), so Rust FFI
 * cannot name them directly. The wrappers are prefixed `slopsys_` on purpose: an
 * exported symbol literally named `slop_arena_new` would clash with the header's
 * static-inline `slop_arena_new` present in every TU. */
#include "slop_runtime.h"

slop_arena* slopsys_arena_new(size_t capacity) {
    slop_arena* a = (slop_arena*)malloc(sizeof(slop_arena));
    if (!a) return NULL;
    *a = slop_arena_new(capacity);
    if (a->base == NULL) { free(a); return NULL; }
    return a;
}

void slopsys_arena_free(slop_arena* arena) {
    if (!arena) return;
    slop_arena_free(arena);
    free(arena);
}

slop_string slopsys_intern_string(const char* data, size_t len) {
    return slop_intern_string(data, len);
}
