#ifndef _STR_H
#define _STR_H

typedef void* STR_T;

STR_T str_create(const char* str);
void str_destroy(STR_T ptr);
STR_T str_copy(STR_T ptr);
void str_cat_char(STR_T ptr, int ch);
void str_cat_str(STR_T ptr, const char* str);
const char* str_raw(STR_T ptr);
void str_clear(STR_T ptr);

#endif /* _STR_H */
