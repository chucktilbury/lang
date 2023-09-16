
#include <stdio.h>
#include <stdint.h>

#include "str.h"
#include "strlst.h"
#include "parser.h"
#include "scanner.h"
#include "ast.h"

//extern ast_module_t* ast_module_root;

int main() {
    yydebug = 0;
    open_file("test.txt");
    yyparse();
    //printf("\nParser ptr: %p (%d)\n", (void*)ast_module_root, TYPEOF(ast_module_root));
    return 0;
}
