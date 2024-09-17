#ifndef ALJP_UTILS_ERROR_H
#define ALJP_UTILS_ERROR_H

// Error Handling

char* __aljp_error_msg = "";

struct __jmp_buf_tag __aljp_error_jmpbuf[1024];

void (*__aljp_error_handlers[256])(char*);


// By default, errors will print to stderr and exit with the error code
// You can change this behavior by setting an error handler for the error code
#define SET_ERROR_HANDLER(x, handler) __aljp_error_handlers[x] = handler;

// This should be called before any errors are thrown if you want to handle them properly
#define SET_ERROR_JMP() int8_t __aljp_error_result = setjmp(__aljp_error_jmpbuf); \
        if (__aljp_error_result) { \
            if (__aljp_error_handlers[__aljp_error_result]) { \
                __aljp_error_handlers[__aljp_error_result](__aljp_error_msg); \
            } else { \
                eprintf(COLOR_FG_RED STYLE_BOLD "Error: " COLOR_FG_RESET "%s\n", __aljp_error_msg); \
                eprintf("Exited with error code: %d\n", __aljp_error_result); \
                exit(__aljp_error_result); \
            } \
        }
#define ERROR(x, msg) __aljp_error_msg = malloc(strlen(msg)); \
        strcpy(__aljp_error_msg, msg); \
        if (__aljp_error_jmpbuf != NULL) { \
            longjmp(__aljp_error_jmpbuf, x); \
        } else { \
            eprintf(COLOR_FG_RED STYLE_BOLD "Error: " COLOR_FG_RESET "%s\n", __aljp_error_msg); \
            eprintf("Exited with error code: %d\n", x); \
            exit(x); \
        }

// By default, the error code is 1, but you can optionally pass a different error code
#define ASSERT(cond, msg, ...) do { \
        if (!(cond)) { \
            DEBUG_LOG(STYLE_BOLD "%s:%d: " COLOR_RED "error: " COLOR_RESET "assertion failed: " STYLE_BOLD "%s\n", __FILE__, __LINE__, #cond); \
            if (__aljp_error_jmpbuf != NULL) { \
                int8_t e = __VA_OPT__(GET_1ST_ARG(__VA_ARGS__)) + 0; \
                ERROR(e ? e : 1, #msg); \
            } else { \
                DEBUG_LOG("SET_ERROR_JMP has not been called! Continuing execution as normal...\n"); \
            } \
        } else { \
            DEBUG_LOG(STYLE_BOLD "%s:%d: " COLOR_GREEN "success: " COLOR_RESET "assertion " STYLE_BOLD "\"%s\"" COLOR_RESET" passed: %s\n", __FILE__, __LINE__, #cond, #msg); \
        } \
    } while (0)

#endif
