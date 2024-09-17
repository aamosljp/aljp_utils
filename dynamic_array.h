#ifndef ALJP_DYNAMIC_ARRAY_H
#define ALJP_DYNAMIC_ARRAY_H

// Dynamic Array
// Dynamic arrays should be defined like this:
// int* DA_DEFER a = DA_NEW(int);
// You can replace int with whatever type you want.

#define DA_INIT_CAP 256

typedef struct {
    int32_t size;
    int32_t capacity;
    char* data;
} __aljp_DAHeader;

#define DA_HEADER(da) ((__aljp_DAHeader*)da - 1)
#define DA_SIZE(da) DA_HEADER(da)->size
#define DA_CAPACITY(da) DA_HEADER(da)->capacity
#define DA_DATA(da) DA_HEADER(da)->data

// For some reason capacity can't go above 8192
#ifdef ALJP_UTILS_MEM_H
#define DA_NEW() safe_calloc(1, sizeof(__aljp_DAHeader)) + sizeof(__aljp_DAHeader);
#define DA_APPEND(da, x) do { \
    if (DA_SIZE(da) + sizeof(da[0]) > DA_CAPACITY(da)) { \
        DA_CAPACITY(da) = DA_CAPACITY(da) == 0 ? DA_INIT_CAP : DA_CAPACITY(da) * 2; \
        DA_DATA(da) = safe_realloc(DA_DATA(da), DA_CAPACITY(da)); \
    } \
    memcpy(&da[DA_SIZE(da)], &x, sizeof(da[0])); \
    DA_SIZE(da) += sizeof(da[0]); \
} while (0)
#else
#define DA_NEW(T) calloc(1, sizeof(__aljp_DAHeader)) + sizeof(__aljp_DAHeader);
#define DA_APPEND(da, x) do { \
    if (DA_SIZE(da) + 1 > DA_CAPACITY(da)) { \
        DA_CAPACITY(da) = DA_CAPACITY(da) == 0 ? DA_INIT_CAP : DA_CAPACITY(da) * 2; \
        DA_DATA(da) = realloc(DA_DATA(da), DA_CAPACITY(da)); \
    } \
    memset(DA_DATA(da) + DA_SIZE(da), x, sizeof(da[0])); \
    DA_SIZE(da)++; \
} while (0)
#endif

// You shouldn't have to use this directly if you defined the array with DA_DEFER
#define DA_FREE(da) do { \
        free(DA_HEADER(da)); \
    } while (0)

void __aljp_da_defer_cleanup(void* ptr) {
    DA_FREE(*((void**)ptr));
}

#define DA_DEFER __attribute__((cleanup(__aljp_da_defer_cleanup)))

#define DA_ITER(da, i, x) for (i = 0; i < DA_SIZE(da)/sizeof(da[0]); x = da[(++i)*sizeof(da[0])])

#endif
