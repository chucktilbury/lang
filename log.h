#ifndef _LOG_H
#define _LOG_H

#ifdef ENA_TRACE
#define TRACE(m, ...)   do { \
        printf("trace: "); \
        printf((m), ## __VA_ARGS__ ); \
        printf("\n"); \
    }while(0)
#else
#define TRACE(m, ...)
#endif

#endif /* _LOG_H */
