#ifndef ALJP_ARGS_H
#define ALJP_ARGS_H

#include "common.h"

char* SHIFT_ARGS(int* argc, char*** argv) {
    (*argc)--;
    return *(*argv)++;
}

#endif
