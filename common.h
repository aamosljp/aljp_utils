#ifndef ALJP_COMMON_H
#define ALJP_COMMON_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <setjmp.h>

#ifdef DEBUG
#define DEBUG_LOG(...) \
        fprintf(stderr, __VA_ARGS__);
#endif
#ifndef DEBUG
#define DEBUG_LOG(fmt,...)
#endif

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define STYLE_BOLD "\x1b[1m"

#define UNREACHABLE do { \
        DEBUG_LOG(stderr, STYLE_BOLD "%s:%d: " COLOR_RED "error: " COLOR_RESET "Should be unreachable!\n", __FILE__, __LINE__); \
    } while (0)

#define DEFER(cleanup_fn) __attribute__((cleanup(cleanup_fn)))

#define ALJP_INIT(x) \
    do { \
        SET_ERROR_JMP; \
    } while (0)

#endif
