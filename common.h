#ifndef ALJP_UTILS_COMMON_H
#define ALJP_UTILS_COMMON_H

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <setjmp.h>

#define COLOR_FG_RESET "\x1b[0m"
#define STYLE_BOLD "\x1b[1m"
#define STYLE_DIM "\x1b[2m"
#define STYLE_ITALIC "\x1b[3m"
#define STYLE_UNDERLINE "\x1b[4m"
#define STYLE_BLINK_SLOW "\x1b[5m"
#define STYLE_BLINK_FAST "\x1b[6m"
#define STYLE_REVERSE "\x1b[7m"
#define STYLE_HIDDEN "\x1b[8m"
#define STYLE_STRIKE "\x1b[9m"
#define STYLE_DEFAULT_FONT "\x1b[10m"
#define STYLE_ALT_FONT(n) "\x1b[1" #n "m" // n is 1-9
#define STYLE_FRAKTUR "\x1b[20m"    // Rarely supported
#define STYLE_DOUBLE_UNDERLINE "\x1b[21m"
#define STYLE_NORMAL "\x1b[22m"
#define STYLE_NO_ITALIC "\x1b[23m"
#define STYLE_NO_UNDERLINE "\x1b[24m"
#define STYLE_NO_BLINK "\x1b[25m"
#define STYLE_PROPORTIONAL_SPACING "\x1b[26m"
#define STYLE_NO_REVERSE "\x1b[27m"
#define STYLE_NO_HIDDEN "\x1b[28m"
#define STYLE_NO_STRIKE "\x1b[29m"
#define COLOR_FG_BLACK "\x1b[30m"
#define COLOR_FG_RED "\x1b[31m"
#define COLOR_FG_GREEN "\x1b[32m"
#define COLOR_FG_YELLOW "\x1b[33m"
#define COLOR_FG_BLUE "\x1b[34m"
#define COLOR_FG_MAGENTA "\x1b[35m"
#define COLOR_FG_CYAN "\x1b[36m"
#define COLOR_FG_WHITE "\x1b[37m"
#define COLOR_FG_CUSTOM(r, g, b) "\x1b[38;2;" #r ";" #g ";" #b "m"
#define COLOR_FG_DEFAULT "\x1b[39m"
#define COLOR_BG_BLACK "\x1b[40m"
#define COLOR_BG_RED "\x1b[41m"
#define COLOR_BG_GREEN "\x1b[42m"
#define COLOR_BG_YELLOW "\x1b[43m"
#define COLOR_BG_BLUE "\x1b[44m"
#define COLOR_BG_MAGENTA "\x1b[45m"
#define COLOR_BG_CYAN "\x1b[46m"
#define COLOR_BG_WHITE "\x1b[47m"
#define COLOR_BG_CUSTOM(r, g, b) "\x1b[48;2;" #r ";" #g ";" #b "m"
#define COLOR_BG_DEFAULT "\x1b[49m"
#define STYLE_NO_PROPORTIONAL_SPACING "\x1b[50m"
#define STYLE_FRAMED "\x1b[51m"
#define STYLE_ENCIRCLED "\x1b[52m"
#define STYLE_OVERLINED "\x1b[53m"
#define STYLE_NO_FRAMED_ENCIRCLED "\x1b[54m"
#define STYLE_NO_OVERLINED "\x1b[55m"
#define STYLE_UNDERLINE_COLOR(r, g, b) "\x1b[58;2;" #r ";" #g ";" #b "m"    // Not in ANSI standard, implemented in at least Kitty, VTE, mintty, and iTerm2
#define STYLE_NO_UNDERLINE_COLOR "\x1b[59m"                                 // Same as above
// Ideograms are rarely supported
#define STYLE_IDEOGRAM_UNDERLINE "\x1b[60m"
#define STYLE_IDEOGRAM_UNDERLINE_DOUBLE "\x1b[61m"
#define STYLE_IDEOGRAM_OVERLINE "\x1b[62m"
#define STYLE_IDEOGRAM_OVERLINE_DOUBLE "\x1b[63m"
#define STYLE_IDEOGRAM_STRESS "\x1b[64m"
#define STYLE_NO_IDEOGRAM "\x1b[65m"
// Superscript and subscript implemented only in mintty afaik
#define STYLE_SUPERSCRIPT "\x1b[73m"
#define STYLE_SUBSCRIPT "\x1b[74m"
#define STYLE_NO_SUPERSCRIPT_SUBSCRIPT "\x1b[75m"
// Bright colors not in standard, orginally implemented by aixterm
#define COLOR_FG_BRIGHT_BLACK "\x1b[90m"
#define COLOR_FG_BRIGHT_RED "\x1b[91m"
#define COLOR_FG_BRIGHT_GREEN "\x1b[92m"
#define COLOR_FG_BRIGHT_YELLOW "\x1b[93m"
#define COLOR_FG_BRIGHT_BLUE "\x1b[94m"
#define COLOR_FG_BRIGHT_MAGENTA "\x1b[95m"
#define COLOR_FG_BRIGHT_CYAN "\x1b[96m"
#define COLOR_FG_BRIGHT_WHITE "\x1b[97m"
#define COLOR_BG_BRIGHT_BLACK "\x1b[100m"
#define COLOR_BG_BRIGHT_RED "\x1b[101m"
#define COLOR_BG_BRIGHT_GREEN "\x1b[102m"
#define COLOR_BG_BRIGHT_YELLOW "\x1b[103m"
#define COLOR_BG_BRIGHT_BLUE "\x1b[104m"
#define COLOR_BG_BRIGHT_MAGENTA "\x1b[105m"
#define COLOR_BG_BRIGHT_CYAN "\x1b[106m"
#define COLOR_BG_BRIGHT_WHITE "\x1b[107m"

#define eprintf(fmt,...) fprintf(stderr, fmt, ##__VA_ARGS__)

#define MIN(x, y) x < y ? x : y

#define MAX(x, y) x > y ? x : y

#define GET_1ST_ARG(x,...) x
#define GET_2ND_ARG(x, y,...) y
#define GET_3RD_ARG(x, y, z,...) z
#define GET_4TH_ARG(x, y, z, w,...) w

#ifdef DEBUG
#define DEBUG_LOG(fmt,...) \
        eprintf(fmt, ##__VA_ARGS__);
#endif
#ifndef DEBUG
#define DEBUG_LOG(...)
#endif

#define UNREACHABLE do { \
        DEBUG_LOG(STYLE_BOLD "%s:%d: " COLOR_FG_RED "error: " COLOR_FG_RESET "Should be unreachable!\n", __FILE__, __LINE__); \
    } while (0)

#define DEFER(cleanup_fn) __attribute__((cleanup(cleanup_fn)))

#ifdef _INCLUDE_ALJP_UTILS_ALL_
    #include "args.h"
    #include "error.h"
    #include "mem.h"
    #include "dynamic_array.h"
    #include "timer.h"
    #include "string.h"
#else
    #ifdef _INCLUDE_ALJP_UTILS_ARGS_
        #include "args.h"
    #endif
    #ifdef _INCLUDE_ALJP_UTILS_ERROR_
        #include "error.h"
    #endif
    #ifdef _INCLUDE_ALJP_UTILS_DYNAMIC_ARRAY_
        #include "dynamic_array.h"
    #endif
    #ifdef _INCLUDE_ALJP_UTILS_TIMER_
        #include "timer.h"
    #endif
    #ifdef _INCLUDE_ALJP_UTILS_MEM_
        #include "mem.h"
    #endif
    #ifdef _INCLUDE_ALJP_UTILS_STRING_
        #include "string.h"
    #endif
#endif

#ifdef ALJP_ERROR_H
#define ALJP_INIT(x) \
    do { \
        SET_ERROR_JMP(); \
    } while (0)
#else
#define ALJP_INIT(x)
#endif

#endif
