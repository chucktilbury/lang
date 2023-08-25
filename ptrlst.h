#ifndef _PTRLST_H
#define _PTRLST_H

typedef struct {
    void** lst;
    unsigned int cap;
    unsigned int len;
} ptrlst_t;

ptrlst_t* ptrlst_create();
void ptrlst_destroy(ptrlst_t* lst);
void ptrlst_add(ptrlst_t* lst, void* ptr);

#endif /* _PTRLST_H */
