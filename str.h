#ifndef _STR_H
#define _STR_H

typedef struct {
    char* buf;
    size_t len;
    size_t cap;
} STR;

STR* str_create(const char* str);
void str_destroy(STR* ptr);
STR* str_copy(STR* ptr);
void str_cat_char(STR* ptr, int ch);
void str_cat_str(STR* ptr, const char* str);
const char* str_raw(STR* ptr);
void str_clear(STR* ptr);

#endif /* _STR_H */
