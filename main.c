
#include <stdio.h>
#include <stdint.h>

#include "str.h"
#include "parser.h"
#include "scanner.h"

int main() {

    open_file("test.txt");
    yyparse();
    return 0;
}
