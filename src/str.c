
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "mem.h"

STR* str_create(const char* str) {

    STR* ptr = _ALLOC_T(STR);
    ptr->len = 0;
    ptr->cap = 1 << 3;
    ptr->buf = _ALLOC(ptr->cap);

    if(str != NULL)
        str_cat_str(ptr, str);

    return ptr;
}

void str_destroy(STR* ptr) {

    if(ptr != NULL) {
        if(ptr->buf != NULL)
            _FREE(ptr->buf);
        _FREE(ptr);
    }
}

STR* str_copy(STR* ptr) {

    return str_create(ptr->buf);
}

void str_cat_char(STR* ptr, int ch) {

    if(ptr->len+2 > ptr->cap) {
        ptr->cap <<= 1;
        ptr->buf = _REALLOC_ARRAY(ptr->buf, char, ptr->cap);
    }

    ptr->buf[ptr->len] = (char)ch;
    ptr->len++;
    ptr->buf[ptr->len] = '\0';
}

void str_cat_str(STR* ptr, const char* str) {

    size_t len = strlen(str);

    if(ptr->len+len > ptr->cap) {
        while(ptr->len+len+1 > ptr->cap)
            ptr->cap <<= 1;
        ptr->buf = _REALLOC_ARRAY(ptr->buf, char, ptr->cap);
    }

    memcpy(&ptr->buf[ptr->len], str, len+1);
    ptr->len += len;

}

const char* str_raw(STR* ptr) {

    return ptr->buf;
}

void str_clear(STR* ptr) {

    ptr->len = 0;
    memset(ptr->buf, 0, ptr->cap);
}
