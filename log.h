#ifndef _LOG_H
#define _LOG_H

#ifdef ENA_TRACE

#define TRACE()   do { \
        printf("trace: %s\n", __func__); \
    }while(0)

#define MSG(m, ...) do { \
        printf("msg: "); \
        printf((m), ##__VA_ARGS__); \
        printf("\n"); \
    } while(0)

#else

#define TRACE()
#define MSG(m, ...)

#endif

#endif /* _LOG_H */
