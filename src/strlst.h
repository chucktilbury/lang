#ifndef _STRLST_H
#define _STRLST_H

#include "ptrlst.h"
#include "str.h"

typedef PTRLST STRLST;

// This is a list of const char*
#define strlst_add(lst, ptr)    ptrlst_add((lst), ((void*)(ptr)))
#define strlst_create()     ptrlst_create()

const char* strlst_raw(STRLST* lst);

#endif
