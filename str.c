
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "mem.h"

typedef struct {
    char* buf;
    size_t len;
    size_t cap;
} str_t;

STR_T str_create(const char* str) {

    str_t* ptr = _ALLOC_T(str_t);
    ptr->len = 0;
    ptr->cap = 1 << 3;
    ptr->buf = _ALLOC(ptr->cap);

    if(str != NULL)
        str_cat_str(ptr, str);

    return ptr;
}

void str_destroy(STR_T ptr) {

    if(ptr != NULL) {
        if(((str_t*)ptr)->buf != NULL)
            _FREE(((str_t*)ptr)->buf);
        _FREE(ptr);
    }
}

STR_T str_copy(STR_T ptr) {

    return str_create(((str_t*)ptr)->buf);
}

void str_cat_char(STR_T ptr, int ch) {

    str_t* p = (str_t*)ptr;
    if(p->len+2 > p->cap) {
        p->cap <<= 1;
        p->buf = _REALLOC_ARRAY(p->buf, char, p->cap);
    }

    p->buf[p->len] = (char)ch;
    p->len++;
    p->buf[p->len] = '\0';
}

void str_cat_str(STR_T ptr, const char* str) {

    str_t* p = (str_t*)ptr;
    size_t len = strlen(str);

    if(p->len+len > p->cap) {
        while(p->len+len+1 > p->cap)
            p->cap <<= 1;
        p->buf = _REALLOC_ARRAY(p->buf, char, p->cap);
    }

    memcpy(&p->buf[p->len], str, len+1);
    p->len += len;

}

const char* str_raw(STR_T ptr) {

    return ((str_t*)ptr)->buf;
}

void str_clear(STR_T ptr) {

    ((str_t*)ptr)->len = 0;
    memset(((str_t*)ptr)->buf, 0, ((str_t*)ptr)->cap);
}
