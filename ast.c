

#include "ast.h"
#include "mem.h"

ast_node_t* ast_create_node(ast_node_type_t type) {

    ast_node_t* node = _ALLOC_T(ast_node_t);
    node->type.type = type;

    return node;
}

void ast_destroy_node(ast_node_t* node) {
    (void)node;
}


