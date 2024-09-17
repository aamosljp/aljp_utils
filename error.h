#ifndef ALJP_ERROR_H
#define ALJP_ERROR_H

#include "common.h"

// Error Handling
// Remember to call SET_ERROR_JMP before erroring

char* error_msg = "";

struct __jmp_buf_tag __aljp_error_jmpbuf[1024];

#define SET_ERROR_JMP int __aljp_error_result = setjmp(__aljp_error_jmpbuf); \
        if (__aljp_error_result) { \
            fprintf(stderr, COLOR_RED STYLE_BOLD "Error: " COLOR_RESET "%s\n", error_msg); \
            exit(__aljp_error_result); \
        }
#define ERROR(x, msg) error_msg = malloc(strlen(msg)); \
        strcpy(error_msg, msg); \
        longjmp(__aljp_error_jmpbuf, x)

#define ASSERT(cond, msg) do { \
        if (!(cond)) { \
            DEBUG_LOG(STYLE_BOLD "%s:%d: " COLOR_RED "error: " COLOR_RESET "assertion failed: " STYLE_BOLD "%s\n", __FILE__, __LINE__, #cond); \
            if (__aljp_error_jmpbuf != NULL) { \
                ERROR(1, #msg); \
            } else { \
                DEBUG_LOG("SET_ERROR_JMP has not been called! Continuing execution as normal...\n"); \
            } \
        } else { \
            DEBUG_LOG(STYLE_BOLD "%s:%d: " COLOR_GREEN "success: " COLOR_RESET "assertion " STYLE_BOLD "\"%s\"" COLOR_RESET" passed: %s\n", __FILE__, __LINE__, #cond, #msg); \
        } \
    } while (0)

#endif
