#ifndef _PTRLST_H
#define _PTRLST_H

typedef struct {
    void** lst;
    unsigned int cap;
    unsigned int len;
} PTRLST;

PTRLST* ptrlst_create();
void ptrlst_destroy(PTRLST* lst);
void ptrlst_add(PTRLST* lst, void* ptr);

#endif /* _PTRLST_H */
