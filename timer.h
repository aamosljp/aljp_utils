#ifndef ALJP_UTILS_TIMER_H
#define ALJP_UTILS_TIMER_H

#include <time.h>

typedef struct {
    const char* name;
    clock_t start_time;
} __aljp_Timer;

static inline void __aljp_start_timer(__aljp_Timer* timer) {
    eprintf("Starting timer [%s]\n", timer->name);
    timer->start_time = clock();
}

static inline void __aljp_stop_timer(__aljp_Timer* timer) {
    clock_t end_time = clock();
    double duration = (double)(end_time - timer->start_time) / CLOCKS_PER_SEC;
    eprintf("Timer [%s] took %.3f seconds\n", timer->name, duration);
}

#define SCOPE_TIMER(name) \
        __aljp_Timer __aljp_timer_##__LINE__ __attribute__((cleanup(__aljp_stop_timer))) = { name }; \
        __aljp_start_timer(&__aljp_timer_##__LINE__)

#endif
