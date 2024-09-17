#ifndef ALJP_UTILS_ARGS_H
#define ALJP_UTILS_ARGS_H

char* SHIFT_ARGS(int* argc, char*** argv) {
    (*argc)--;
    return *(*argv)++;
}

#endif
