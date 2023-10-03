
#include "ptrlst.h"
#include "mem.h"

PTRLST* ptrlst_create() {

    PTRLST* lst = _ALLOC_T(PTRLST);
    lst->len = 0;
    lst->cap = 1 << 3;
    lst->lst = _ALLOC_ARRAY(void*, lst->cap);

    return lst;
}

void ptrlst_destroy(PTRLST* lst) {

    if(lst != NULL) {
        _FREE(lst->lst);
        _FREE(lst);
    }
}

void ptrlst_add(PTRLST* lst, void* ptr) {

    if(lst->len+1 > lst->cap) {
        lst->cap <<= 1;
        lst->lst = _REALLOC_ARRAY(lst->lst, void*, lst->cap);
    }

    lst->lst[lst->len] = ptr;
    lst->len++;
}
