#ifndef _AST_H
#define _AST_H

#include "ast_types.h"
#include "ast_data.h"

typedef struct {
    ast_node_type_t type;
} ast_type_t;

typedef struct _ast_node_t_ {
    // Cast to this to get the actual type.
    ast_type_t type;

    // Every attribute is in a list like this. If there is no
    // list, then this just points to the attribute. The code
    // that knows about the node type knows whether this is a
    // list or not. Only terminal symbols are not lists. A non-
    // terminal symbol may or may not be a list, depending on
    // the type.
    void* attribs;

    // Actual list pointers. These pointers manage peer nodes.
    // These are not pointers to attributes of this node, but
    // pointers to other nodes.
    struct _ast_node_t_* first;
    struct _ast_node_t_* last;
    struct _ast_node_t_* next;
} ast_node_t;


ast_node_t* ast_create_node(ast_node_type_t type);
void ast_destroy_node(ast_node_t* lst);


#endif /* _AST_H */
