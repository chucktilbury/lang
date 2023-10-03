#include <stdio.h>
#include <stdint.h>

#include "ast.h"
#include "mem.h"
#include "str.h"
#include "log.h"
#include "scanner.h"

/*
 *  module
 *      : module_body
 *      ;
 */
struct _ast_module_* create_module() {

    TRACE();
    struct _ast_module_* ptr = _ALLOC_T(struct _ast_module_);
    ptr->type.type = AST_MODULE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  module_element
 *      : namespace_element
 *      | import_statement
 *      | entry_definition
 *      ;
 */
struct _ast_module_element_* create_module_element() {

    TRACE();
    struct _ast_module_element_* ptr = _ALLOC_T(struct _ast_module_element_);
    ptr->type.type = AST_MODULE_ELEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  module_body
 *      : module_element
 *      | module_body module_element
 *      ;
 */
struct _ast_module_body_* create_module_body() {

    TRACE();
    struct _ast_module_body_* ptr = _ALLOC_T(struct _ast_module_body_);
    ptr->type.type = AST_MODULE_BODY;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  entry_definition
 *      : ENTRY func_block
 *      ;
 */
struct _ast_entry_definition_* create_entry_definition() {

    TRACE();
    struct _ast_entry_definition_* ptr = _ALLOC_T(struct _ast_entry_definition_);
    ptr->type.type = AST_ENTRY_DEFINITION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  scope
 *      : PUBLIC
 *      | PRIVATE
 *      | PROTECTED
 *      ;
 */
struct _ast_scope_* create_scope() {

    TRACE();
    struct _ast_scope_* ptr = _ALLOC_T(struct _ast_scope_);
    ptr->type.type = AST_SCOPE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  type_name
 *      : compound_name
 *      | FLOAT
 *      | INTEGER
 *      | UNSIGNED
 *      | STRING
 *      | DICT
 *      | LIST
 *      | BOOLEAN
 *      | NOTHING
 *      ;
 */
struct _ast_type_name_* create_type_name() {

    TRACE();
    struct _ast_type_name_* ptr = _ALLOC_T(struct _ast_type_name_);
    ptr->type.type = AST_TYPE_NAME;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  compound_reference
 *      : compound_reference_element
 *      | compound_reference DOT compound_reference_element
 *      ;
 */
struct _ast_compound_reference_* create_compound_reference() {

    TRACE();
    struct _ast_compound_reference_* ptr = _ALLOC_T(struct _ast_compound_reference_);
    ptr->type.type = AST_COMPOUND_REFERENCE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  compound_reference_element
 *      : compound_name
 *      | func_reference
 *      | array_reference
 *      ;
 */
struct _ast_compound_reference_element_* create_compound_reference_element() {

    TRACE();
    struct _ast_compound_reference_element_* ptr = _ALLOC_T(struct _ast_compound_reference_element_);
    ptr->type.type = AST_COMPOUND_REFERENCE_ELEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  compound_name
 *      : SYMBOL
 *      | COMPOUND
 *      ;
 */
struct _ast_compound_name_* create_compound_name() {

    TRACE();
    struct _ast_compound_name_* ptr = _ALLOC_T(struct _ast_compound_name_);
    ptr->type.type = AST_COMPOUND_NAME;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  formatted_string
 *      : STRG_CONST
 *      | STRG_CONST OPAREN CPAREN
 *      | STRG_CONST OPAREN expr_list CPAREN
 *      ;
 */
struct _ast_formatted_string_* create_formatted_string() {

    TRACE();
    struct _ast_formatted_string_* ptr = _ALLOC_T(struct _ast_formatted_string_);
    ptr->type.type = AST_FORMATTED_STRING;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  func_reference
 *      : compound_name OPAREN CPAREN
 *      | compound_name OPAREN expr_list CPAREN
 *      ;
 */
struct _ast_func_reference_* create_func_reference() {

    TRACE();
    struct _ast_func_reference_* ptr = _ALLOC_T(struct _ast_func_reference_);
    ptr->type.type = AST_FUNC_REFERENCE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  array_reference
 *      : compound_name array_reference_list
 *      ;
 */
struct _ast_array_reference_* create_array_reference() {

    TRACE();
    struct _ast_array_reference_* ptr = _ALLOC_T(struct _ast_array_reference_);
    ptr->type.type = AST_ARRAY_REFERENCE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  array_reference_list
 *      : OBRACE expression CBRACE
 *      | array_reference_list OBRACE expression CBRACE
 *      ;
 */
struct _ast_array_reference_list_* create_array_reference_list() {

    TRACE();
    struct _ast_array_reference_list_* ptr = _ALLOC_T(struct _ast_array_reference_list_);
    ptr->type.type = AST_ARRAY_REFERENCE_LIST;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  namespace_definition
 *      : NAMESPACE SYMBOL OBLOCK namespace_block CBLOCK
 *      ;
 */
struct _ast_namespace_definition_* create_namespace_definition() {

    TRACE();
    struct _ast_namespace_definition_* ptr = _ALLOC_T(struct _ast_namespace_definition_);
    ptr->type.type = AST_NAMESPACE_DEFINITION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  namespace_block
 *      : namespace_element
 *      | namespace_block namespace_element
 *      ;
 */
struct _ast_namespace_block_* create_namespace_block() {

    TRACE();
    struct _ast_namespace_block_* ptr = _ALLOC_T(struct _ast_namespace_block_);
    ptr->type.type = AST_NAMESPACE_BLOCK;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  namespace_element
 *      : namespace_definition
 *      | class_definition
 *      | func_definition
 *      | ctor_definition
 *      | dtor_definition
 *      | var_declaration
 *      | scope
 *      ;
 */
struct _ast_namespace_element_* create_namespace_element() {

    TRACE();
    struct _ast_namespace_element_* ptr = _ALLOC_T(struct _ast_namespace_element_);
    ptr->type.type = AST_NAMESPACE_ELEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  class_definition
 *      : CLASS SYMBOL class_parameters class_block
 *      ;
 */
struct _ast_class_definition_* create_class_definition() {

    TRACE();
    struct _ast_class_definition_* ptr = _ALLOC_T(struct _ast_class_definition_);
    ptr->type.type = AST_CLASS_DEFINITION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  class_parameters
 *      : %empty
 *      | OPAREN CPAREN
 *      | OPAREN compound_name CPAREN
 *      ;
 */
struct _ast_class_parameters_* create_class_parameters() {

    TRACE();
    struct _ast_class_parameters_* ptr = _ALLOC_T(struct _ast_class_parameters_);
    ptr->type.type = AST_CLASS_PARAMETERS;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  class_block
 *      : OBLOCK CBLOCK
 *      | OBLOCK class_body CBLOCK
 *      ;
 */
struct _ast_class_block_* create_class_block() {

    TRACE();
    struct _ast_class_block_* ptr = _ALLOC_T(struct _ast_class_block_);
    ptr->type.type = AST_CLASS_BLOCK;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  class_body
 *      : class_body_element
 *      | class_body class_body_element
 *      ;
 */
struct _ast_class_body_* create_class_body() {

    TRACE();
    struct _ast_class_body_* ptr = _ALLOC_T(struct _ast_class_body_);
    ptr->type.type = AST_CLASS_BODY;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  class_body_element
 *      : var_declaration
 *      | func_declaration
 *      | scope
 *      ;
 */
struct _ast_class_body_element_* create_class_body_element() {

    TRACE();
    struct _ast_class_body_element_* ptr = _ALLOC_T(struct _ast_class_body_element_);
    ptr->type.type = AST_CLASS_BODY_ELEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  var_declaration
 *      : type_name SYMBOL
 *      ;
 */
struct _ast_var_declaration_* create_var_declaration() {

    TRACE();
    struct _ast_var_declaration_* ptr = _ALLOC_T(struct _ast_var_declaration_);
    ptr->type.type = AST_VAR_DECLARATION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  func_declaration
 *      : type_name SYMBOL func_decl_parms
 *      | CREATE func_decl_parms
 *      | DESTROY
 *      ;
 */
struct _ast_func_declaration_* create_func_declaration() {

    TRACE();
    struct _ast_func_declaration_* ptr = _ALLOC_T(struct _ast_func_declaration_);
    ptr->type.type = AST_FUNC_DECLARATION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  func_decl_parms
 *      : OPAREN CPAREN
 *      | OPAREN func_decl_parms_list CPAREN
 *      ;
 */
struct _ast_func_decl_parms_* create_func_decl_parms() {

    TRACE();
    struct _ast_func_decl_parms_* ptr = _ALLOC_T(struct _ast_func_decl_parms_);
    ptr->type.type = AST_FUNC_DECL_PARMS;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  func_decl_parms_list
 *      : func_decl_parms_elem
 *      | func_decl_parms_list COMMA func_decl_parms_elem
 *      ;
 */
struct _ast_func_decl_parms_list_* create_func_decl_parms_list() {

    TRACE();
    struct _ast_func_decl_parms_list_* ptr = _ALLOC_T(struct _ast_func_decl_parms_list_);
    ptr->type.type = AST_FUNC_DECL_PARMS_LIST;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  func_decl_parms_elem
 *      : type_name SYMBOL
 *      ;
 */
struct _ast_func_decl_parms_elem_* create_func_decl_parms_elem() {

    TRACE();
    struct _ast_func_decl_parms_elem_* ptr = _ALLOC_T(struct _ast_func_decl_parms_elem_);
    ptr->type.type = AST_FUNC_DECL_PARMS_ELEM;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  bool_literal
 *      : TRUE
 *      | FALSE
 *      ;
 */
struct _ast_bool_literal_* create_bool_literal() {

    TRACE();
    struct _ast_bool_literal_* ptr = _ALLOC_T(struct _ast_bool_literal_);
    ptr->type.type = AST_BOOL_LITERAL;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  primary
 *      : compound_reference
 *      | const_expression
 *      | OPAREN expression CPAREN
 *      ;
 */
struct _ast_primary_* create_primary() {

    TRACE();
    struct _ast_primary_* ptr = _ALLOC_T(struct _ast_primary_);
    ptr->type.type = AST_PRIMARY;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  const_expression
 *      : formatted_string
 *      | bool_literal
 *      | FLOAT_CONST
 *      | INT_CONST
 *      | UNSIGNED_CONST
 *      ;
 */
struct _ast_const_expression_* create_const_expression() {

    TRACE();
    struct _ast_const_expression_* ptr = _ALLOC_T(struct _ast_const_expression_);
    ptr->type.type = AST_CONST_EXPRESSION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  expression
 *      : primary
 *      | expression AND expression
 *      | expression OR expression
 *      | expression EQU expression
 *      | expression NEQU expression
 *      | expression LORE expression
 *      | expression GORE expression
 *      | expression OPOINT expression
 *      | expression CPOINT expression
 *      | expression ADD expression
 *      | expression SUB expression
 *      | expression MUL expression
 *      | expression DIV expression
 *      | expression MOD expression
 *      | expression POW expression
 *      | NOT expression %prec UNARY
 *      | SUB expression %prec UNARY
 *      | cast_expr %prec CAST
 *      ;
 */
struct _ast_expression_* create_expression() {

    TRACE();
    struct _ast_expression_* ptr = _ALLOC_T(struct _ast_expression_);
    ptr->type.type = AST_EXPRESSION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  cast_expr
 *      : OPOINT type_name CPOINT expression
 *      ;
 */
struct _ast_cast_expr_* create_cast_expr() {

    TRACE();
    struct _ast_cast_expr_* ptr = _ALLOC_T(struct _ast_cast_expr_);
    ptr->type.type = AST_CAST_EXPR;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  expr_list
 *      : expression
 *      | expr_list COMMA expression
 *      ;
 */
struct _ast_expr_list_* create_expr_list() {

    TRACE();
    struct _ast_expr_list_* ptr = _ALLOC_T(struct _ast_expr_list_);
    ptr->type.type = AST_EXPR_LIST;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  member
 *      : SYMBOL COLON
 *      ;
 */
struct _ast_member_* create_member() {

    TRACE();
    struct _ast_member_* ptr = _ALLOC_T(struct _ast_member_);
    ptr->type.type = AST_MEMBER;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  func_definition
 *      : type_name member SYMBOL func_decl_parms func_block
 *      ;
 */
struct _ast_func_definition_* create_func_definition() {

    TRACE();
    struct _ast_func_definition_* ptr = _ALLOC_T(struct _ast_func_definition_);
    ptr->type.type = AST_FUNC_DEFINITION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  ctor_definition
 *      : member OPAREN func_decl_parms CPAREN func_block
 *      ;
 */
struct _ast_ctor_definition_* create_ctor_definition() {

    TRACE();
    struct _ast_ctor_definition_* ptr = _ALLOC_T(struct _ast_ctor_definition_);
    ptr->type.type = AST_CTOR_DEFINITION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  dtor_definition
 *      : member DESTROY func_block
 *      ;
 */
struct _ast_dtor_definition_* create_dtor_definition() {

    TRACE();
    struct _ast_dtor_definition_* ptr = _ALLOC_T(struct _ast_dtor_definition_);
    ptr->type.type = AST_DTOR_DEFINITION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  func_block
 *      : OBLOCK CBLOCK
 *      | OBLOCK func_content CBLOCK
 *      ;
 */
struct _ast_func_block_* create_func_block() {

    TRACE();
    struct _ast_func_block_* ptr = _ALLOC_T(struct _ast_func_block_);
    ptr->type.type = AST_FUNC_BLOCK;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  assignment_oper
 *      : ASSIGN
 *      | ADD_ASSIGN
 *      | SUB_ASSIGN
 *      | MUL_ASSIGN
 *      | DIV_ASSIGN
 *      | MOD_ASSIGN
 *      ;
 */
struct _ast_assignment_oper_* create_assignment_oper() {

    TRACE();
    struct _ast_assignment_oper_* ptr = _ALLOC_T(struct _ast_assignment_oper_);
    ptr->type.type = AST_ASSIGNMENT_OPER;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  assignment
 *      : assignment_oper expression
 *      ;
 */
struct _ast_assignment_* create_assignment() {

    TRACE();
    struct _ast_assignment_* ptr = _ALLOC_T(struct _ast_assignment_);
    ptr->type.type = AST_ASSIGNMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  data_definition
 *      : var_declaration
 *      | var_declaration assignment
 *      ;
 */
struct _ast_data_definition_* create_data_definition() {

    TRACE();
    struct _ast_data_definition_* ptr = _ALLOC_T(struct _ast_data_definition_);
    ptr->type.type = AST_DATA_DEFINITION;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  func_content
 *      : func_content_elem
 *      | func_content func_content_elem
 *      ;
 */
struct _ast_func_content_* create_func_content() {

    TRACE();
    struct _ast_func_content_* ptr = _ALLOC_T(struct _ast_func_content_);
    ptr->type.type = AST_FUNC_CONTENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  func_content_elem
 *      : func_block
 *      | data_definition
 *      | compound_reference
 *      | compound_reference assignment
 *      | if_else_clause
 *      | while_clause
 *      | do_clause
 *      | for_clause
 *      | switch_case_clause
 *      | try_except_clause
 *      | return_statement
 *      | raise_statement
 *      | exit_statement
 *      | yield_statement
 *      | trace_statement
 *      | print_statement
 *      | break_statement
 *      | cont_statement
 *      | inline_block
 *      ;
 */
struct _ast_func_content_elem_* create_func_content_elem() {

    TRACE();
    struct _ast_func_content_elem_* ptr = _ALLOC_T(struct _ast_func_content_elem_);
    ptr->type.type = AST_FUNC_CONTENT_ELEM;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  inline_block
 *      : IBEGIN STRG_CONST IEND
 *      ;
 */
struct _ast_inline_block_* create_inline_block() {

    TRACE();
    struct _ast_inline_block_* ptr = _ALLOC_T(struct _ast_inline_block_);
    ptr->type.type = AST_INLINE_BLOCK;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  print_statement
 *      : PRINT
 *      | PRINT OPAREN CPAREN
 *      | PRINT OPAREN formatted_string CPAREN
 *      ;
 */
struct _ast_print_statement_* create_print_statement() {

    TRACE();
    struct _ast_print_statement_* ptr = _ALLOC_T(struct _ast_print_statement_);
    ptr->type.type = AST_PRINT_STATEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  break_statement
 *      : BREAK
 *      ;
 */
struct _ast_break_statement_* create_break_statement() {

    TRACE();
    struct _ast_break_statement_* ptr = _ALLOC_T(struct _ast_break_statement_);
    ptr->type.type = AST_BREAK_STATEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  cont_statement
 *      : CONTINUE
 *      ;
 */
struct _ast_cont_statement_* create_cont_statement() {

    TRACE();
    struct _ast_cont_statement_* ptr = _ALLOC_T(struct _ast_cont_statement_);
    ptr->type.type = AST_CONT_STATEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  trace_statement
 *      : TRACE
 *      | TRACE OPAREN CPAREN
 *      | TRACE OPAREN formatted_string CPAREN
 *      ;
 */
struct _ast_trace_statement_* create_trace_statement() {

    TRACE();
    struct _ast_trace_statement_* ptr = _ALLOC_T(struct _ast_trace_statement_);
    ptr->type.type = AST_TRACE_STATEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  yield_statement
 *      : YIELD OPAREN SYMBOL CPAREN
 *      ;
 */
struct _ast_yield_statement_* create_yield_statement() {

    TRACE();
    struct _ast_yield_statement_* ptr = _ALLOC_T(struct _ast_yield_statement_);
    ptr->type.type = AST_YIELD_STATEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  exit_statement
 *      : EXIT OPAREN expression CPAREN
 *      ;
 */
struct _ast_exit_statement_* create_exit_statement() {

    TRACE();
    struct _ast_exit_statement_* ptr = _ALLOC_T(struct _ast_exit_statement_);
    ptr->type.type = AST_EXIT_STATEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  return_statement
 *      : RETURN
 *      | RETURN OPAREN CPAREN
 *      | RETURN OPAREN expression CPAREN
 *      ;
 */
struct _ast_return_statement_* create_return_statement() {

    TRACE();
    struct _ast_return_statement_* ptr = _ALLOC_T(struct _ast_return_statement_);
    ptr->type.type = AST_RETURN_STATEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  raise_statement
 *      : RAISE OPAREN compound_name CPAREN
 *      ;
 */
struct _ast_raise_statement_* create_raise_statement() {

    TRACE();
    struct _ast_raise_statement_* ptr = _ALLOC_T(struct _ast_raise_statement_);
    ptr->type.type = AST_RAISE_STATEMENT;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  if_else_clause
 *      : if_clause
 *      | if_clause else_clause_list
 *      | if_clause else_clause_list else_clause_final
 *      ;
 */
struct _ast_if_else_clause_* create_if_else_clause() {

    TRACE();
    struct _ast_if_else_clause_* ptr = _ALLOC_T(struct _ast_if_else_clause_);
    ptr->type.type = AST_IF_ELSE_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  if_clause
 *      : IF OPAREN expression CPAREN func_block
 *      ;
 */
struct _ast_if_clause_* create_if_clause() {

    TRACE();
    struct _ast_if_clause_* ptr = _ALLOC_T(struct _ast_if_clause_);
    ptr->type.type = AST_IF_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  else_clause
 *      : ELSE OPAREN expression CPAREN func_block
 *      ;
 */
struct _ast_else_clause_* create_else_clause() {

    TRACE();
    struct _ast_else_clause_* ptr = _ALLOC_T(struct _ast_else_clause_);
    ptr->type.type = AST_ELSE_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  else_clause_list
 *      : else_clause
 *      | else_clause_list else_clause
 *      ;
 */
struct _ast_else_clause_list_* create_else_clause_list() {

    TRACE();
    struct _ast_else_clause_list_* ptr = _ALLOC_T(struct _ast_else_clause_list_);
    ptr->type.type = AST_ELSE_CLAUSE_LIST;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  else_clause_final
 *      : ELSE OPAREN CPAREN func_block
 *      | ELSE func_block
 *      ;
 */
struct _ast_else_clause_final_* create_else_clause_final() {

    TRACE();
    struct _ast_else_clause_final_* ptr = _ALLOC_T(struct _ast_else_clause_final_);
    ptr->type.type = AST_ELSE_CLAUSE_FINAL;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  while_clause
 *      : WHILE OPAREN expression CPAREN func_block
 *      ;
 */
struct _ast_while_clause_* create_while_clause() {

    TRACE();
    struct _ast_while_clause_* ptr = _ALLOC_T(struct _ast_while_clause_);
    ptr->type.type = AST_WHILE_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  do_clause
 *      : DO func_block WHILE OPAREN expression CPAREN
 *      ;
 */
struct _ast_do_clause_* create_do_clause() {

    TRACE();
    struct _ast_do_clause_* ptr = _ALLOC_T(struct _ast_do_clause_);
    ptr->type.type = AST_DO_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  for_clause
 *      : FOR OPAREN SYMBOL IN compound_reference CPAREN func_block
 *      | FOR OPAREN SYMBOL IN expression TO expression CPAREN func_block
 *      ;
 */
struct _ast_for_clause_* create_for_clause() {

    TRACE();
    struct _ast_for_clause_* ptr = _ALLOC_T(struct _ast_for_clause_);
    ptr->type.type = AST_FOR_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  switch_case_clause
 *      : switch_clause case_clause_list case_clause_final
 *      ;
 */
struct _ast_switch_case_clause_* create_switch_case_clause() {

    TRACE();
    struct _ast_switch_case_clause_* ptr = _ALLOC_T(struct _ast_switch_case_clause_);
    ptr->type.type = AST_SWITCH_CASE_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  switch_clause
 *      : SWITCH OPAREN expression CPAREN OBLOCK
 *      ;
 */
struct _ast_switch_clause_* create_switch_clause() {

    TRACE();
    struct _ast_switch_clause_* ptr = _ALLOC_T(struct _ast_switch_clause_);
    ptr->type.type = AST_SWITCH_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  case_clause
 *      : CASE OPAREN const_expression CPAREN func_block
 *      ;
 */
struct _ast_case_clause_* create_case_clause() {

    TRACE();
    struct _ast_case_clause_* ptr = _ALLOC_T(struct _ast_case_clause_);
    ptr->type.type = AST_CASE_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  case_clause_list
 *      : case_clause
 *      | case_clause_list case_clause
 *      ;
 */
struct _ast_case_clause_list_* create_case_clause_list() {

    TRACE();
    struct _ast_case_clause_list_* ptr = _ALLOC_T(struct _ast_case_clause_list_);
    ptr->type.type = AST_CASE_CLAUSE_LIST;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  case_clause_final
 *      : CBLOCK
 *      | DEFAULT func_block CBLOCK
 *      ;
 */
struct _ast_case_clause_final_* create_case_clause_final() {

    TRACE();
    struct _ast_case_clause_final_* ptr = _ALLOC_T(struct _ast_case_clause_final_);
    ptr->type.type = AST_CASE_CLAUSE_FINAL;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  try_except_clause
 *      : try_clause except_clause_list except_clause_final
 *      ;
 */
struct _ast_try_except_clause_* create_try_except_clause() {

    TRACE();
    struct _ast_try_except_clause_* ptr = _ALLOC_T(struct _ast_try_except_clause_);
    ptr->type.type = AST_TRY_EXCEPT_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  try_clause
 *      : TRY func_block
 *      ;
 */
struct _ast_try_clause_* create_try_clause() {

    TRACE();
    struct _ast_try_clause_* ptr = _ALLOC_T(struct _ast_try_clause_);
    ptr->type.type = AST_TRY_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  except_clause
 *      : EXCEPT OPAREN compound_name CPAREN func_block
 *      ;
 */
struct _ast_except_clause_* create_except_clause() {

    TRACE();
    struct _ast_except_clause_* ptr = _ALLOC_T(struct _ast_except_clause_);
    ptr->type.type = AST_EXCEPT_CLAUSE;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  except_clause_list
 *      : except_clause
 *      | except_clause_list except_clause
 *      ;
 */
struct _ast_except_clause_list_* create_except_clause_list() {

    TRACE();
    struct _ast_except_clause_list_* ptr = _ALLOC_T(struct _ast_except_clause_list_);
    ptr->type.type = AST_EXCEPT_CLAUSE_LIST;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

/*
 *  except_clause_final
 *      : EXCEPT OPAREN CPAREN func_block
 *      | EXCEPT func_block
 *      ;
 */
struct _ast_except_clause_final_* create_except_clause_final() {

    TRACE();
    struct _ast_except_clause_final_* ptr = _ALLOC_T(struct _ast_except_clause_final_);
    ptr->type.type = AST_EXCEPT_CLAUSE_FINAL;
    ptr->type.col = get_col_no();
    ptr->type.line = get_line_no();
    ptr->type.fname = get_file_name();


    return ptr;
}

