
#include <stdint.h>
#include <stdio.h>

#include "util.h"
#include "ast.h"
#include "parser.h"
#include "scanner.h"

// extern ast_module_t* ast_module_root;

// these values belong is a global parser state data strucutre.
CmdLine cl;
int depth;

CmdLine get_cmd_line(int argc, char** argv) {

    CmdLine cl = create_cmd_line("Test program for the Simple parser.");
    add_cmd(cl, "-p", "depth", "Set the depth of the test.", "10", CMD_INT);
    add_cmd(cl, "-d", "dpar", "Set the state of the parser to debug state", NULL, CMD_BOOL);
    add_cmd(cl, "", "file", "name of the file to test.", NULL, CMD_STR | CMD_REQD);
    parse_cmd_line(cl, argc, argv);

    return cl;
}

int main(int argc, char** argv) {

    cl = get_cmd_line(argc, argv);

    yydebug = get_cmd_bool(cl, "dpar");
    depth = get_cmd_int(cl, "depth");

    open_file(get_cmd_raw(cl, "file"));

    if(depth > 1)
        yyparse();

    // printf("\nParser ptr: %p (%d)\n", (void*)ast_module_root, TYPEOF(ast_module_root));
    return 0;
}
