#ifndef ALJP_UTILS_STRING_H
#define ALJP_UTILS_STRING_H

#define STRCPY(dst, src, sz) do { \
        strncpy(dst, src, sz); \
        dst[sz - 1] = '\0'; \
    } while (0)

#define STRCAT(dst, src, sz) do { \
        strncat(dst, src, sz); \
        dst[sz - 1] = '\0'; \
    } while (0)

#endif
