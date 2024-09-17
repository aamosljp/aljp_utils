#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "common.h"

// Dynamic Array
// Dynamic arrays should be defined like this:
// int* DA_DEFER a = DA_NEW(int);
// You can replace int with whatever type you want.

#define DA_INIT_CAP 256

typedef struct {
    int size;
    int capacity;
    char *data;
} DAHeader;

#define DA_HEADER(da) ((DAHeader*)da - 1)
#define DA_SIZE(da) DA_HEADER(da)->size
#define DA_CAPACITY(da) DA_HEADER(da)->capacity
#define DA_DATA(da) DA_HEADER(da)->data

#define DA_NEW(T) malloc(sizeof(DAHeader)) + sizeof(DAHeader);

// For some reason capacity can't go above 8192
#define DA_APPEND(da, x) do { \
        if (DA_SIZE(da) + 1 > DA_CAPACITY(da)) { \
            DA_CAPACITY(da) = DA_CAPACITY(da) == 0 ? DA_INIT_CAP : DA_CAPACITY(da) * 2; \
            DA_DATA(da) = realloc(DA_DATA(da), DA_CAPACITY(da)*sizeof(da[0])); \
        } \
        da[DA_SIZE(da)] = x; \
        DA_SIZE(da) += sizeof(da[0]); \
    } while (0)

// You shouldn't have to use this directly if you defined the array with DA_DEFER
#define DA_FREE(da) do { \
        free(DA_HEADER(da)); \
    } while (0)

void da_defer_cleanup(void* ptr) {
    DA_FREE(*((void**)ptr));
}

#define DA_DEFER __attribute__((cleanup(da_defer_cleanup)))

#define DA_ITER(da, i, x) for (i = 0; i < DA_SIZE(da)/sizeof(da[0]); x = da[(++i)*sizeof(da[0])])

#endif
