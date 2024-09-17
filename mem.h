#ifndef ALJP_UTILS_MEM_H
#define ALJP_UTILS_MEM_H

#include <stdlib.h>

static inline void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        eprintf("Failed to allocate memory of size %ld\n", size);
        perror(STYLE_BOLD COLOR_FG_RED "Error" COLOR_FG_RESET);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

static inline void* safe_calloc(size_t count, size_t size) {
    void* ptr = calloc(count, size);
    if (ptr == NULL) {
        eprintf("Failed to allocate memory of size %ld\n", size);
        perror(STYLE_BOLD COLOR_FG_RED "Error" COLOR_FG_RESET);
        exit(EXIT_FAILURE);
    }
    return ptr;
}

static inline void* safe_realloc(void* ptr, size_t size) {
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        eprintf("Failed to allocate memory of size %ld\n", size);
        perror(STYLE_BOLD COLOR_FG_RED "Error" COLOR_FG_RESET);
        exit(EXIT_FAILURE);
    }
    return new_ptr != NULL ? new_ptr : ptr;
}

#endif
