
#include <stdio.h>

#include "strlst.h"

const char* strlst_raw(STRLST* lst) {

    STR* str = str_create(NULL);

    for(size_t x = 0; x < lst->len; x++) {
        str_cat_str(str, lst->lst[x]);
        if(x+1 < lst->len)
            str_cat_char(str, '.');
    }

    return str_raw(str);
}
