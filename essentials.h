#ifndef __ALJP_ESSENTIALS_H__
#define __ALJP_ESSENTIALS_H__

#include <stdlib.h>
#include <stdint.h>

#define DA_INIT_CAP 256

// Dynamic Array
typedef struct {
    uint32_t size;
    uint32_t capacity;
    char* data;
} DAHeader;

#define DA_HEADER(da) ((DAHeader*)(da))[-1]
#define DA_SIZE(da) ((DAHeader*)(da))[-1].size
#define DA_CAPACITY(da) ((DAHeader*)(da))[-1].capacity
#define DA_DATA(da) ((DAHeader*)(da))[-1].data

#define DA_INIT(da) do { \
        da = malloc(sizeof(DAHeader) + sizeof(da[0])); \
        da += sizeof(DAHeader); \
        DA_CAPACITY(da) = 0; \
        DA_SIZE(da) = 0; \
    } while (0)

#define DA_APPEND(da, x) do { \
        if (DA_SIZE(da) + 1 > DA_CAPACITY(da)) { \
            DA_CAPACITY(da) = DA_CAPACITY(da) == 0? DA_INIT_CAP : DA_CAPACITY(da) * 2; \
            da = realloc(DA_DATA(da), DA_CAPACITY(da)*sizeof(da[0])); \
        } \
        da[DA_SIZE(da)] = x; \
        DA_SIZE(da) += 1; \
    } while (0)

#define DA_FREE(da) do { \
        free(da); \
    } while (0)

#endif
