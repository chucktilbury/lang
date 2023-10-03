#ifndef _AST_H
#define _AST_H

typedef enum {
    AST_MODULE,
    AST_MODULE_ELEMENT,
    AST_MODULE_BODY,
    AST_ENTRY_DEFINITION,
    AST_SCOPE,
    AST_TYPE_NAME,
    AST_COMPOUND_REFERENCE,
    AST_COMPOUND_REFERENCE_ELEMENT,
    AST_COMPOUND_NAME,
    AST_FORMATTED_STRING,
    AST_FUNC_REFERENCE,
    AST_ARRAY_REFERENCE,
    AST_ARRAY_REFERENCE_LIST,
    AST_IMPORT_STATEMENT,
    AST_NAMESPACE_DEFINITION,
    AST_NAMESPACE_BLOCK,
    AST_NAMESPACE_ELEMENT,
    AST_CLASS_DEFINITION,
    AST_CLASS_PARAMETERS,
    AST_CLASS_BLOCK,
    AST_CLASS_BODY,
    AST_CLASS_BODY_ELEMENT,
    AST_VAR_DECLARATION,
    AST_FUNC_DECLARATION,
    AST_FUNC_DECL_PARMS,
    AST_FUNC_DECL_PARMS_LIST,
    AST_FUNC_DECL_PARMS_ELEM,
    AST_BOOL_LITERAL,
    AST_PRIMARY,
    AST_CONST_EXPRESSION,
    AST_EXPRESSION,
    AST_CAST_EXPR,
    AST_EXPR_LIST,
    AST_MEMBER,
    AST_FUNC_DEFINITION,
    AST_CTOR_DEFINITION,
    AST_DTOR_DEFINITION,
    AST_FUNC_BLOCK,
    AST_ASSIGNMENT_OPER,
    AST_ASSIGNMENT,
    AST_DATA_DEFINITION,
    AST_FUNC_CONTENT,
    AST_FUNC_CONTENT_ELEM,
    AST_INLINE_BLOCK,
    AST_PRINT_STATEMENT,
    AST_BREAK_STATEMENT,
    AST_CONT_STATEMENT,
    AST_TRACE_STATEMENT,
    AST_YIELD_STATEMENT,
    AST_EXIT_STATEMENT,
    AST_RETURN_STATEMENT,
    AST_RAISE_STATEMENT,
    AST_IF_ELSE_CLAUSE,
    AST_IF_CLAUSE,
    AST_ELSE_CLAUSE,
    AST_ELSE_CLAUSE_LIST,
    AST_ELSE_CLAUSE_FINAL,
    AST_WHILE_CLAUSE,
    AST_DO_CLAUSE,
    AST_FOR_CLAUSE,
    AST_SWITCH_CASE_CLAUSE,
    AST_SWITCH_CLAUSE,
    AST_CASE_CLAUSE,
    AST_CASE_CLAUSE_LIST,
    AST_CASE_CLAUSE_FINAL,
    AST_TRY_EXCEPT_CLAUSE,
    AST_TRY_CLAUSE,
    AST_EXCEPT_CLAUSE,
    AST_EXCEPT_CLAUSE_LIST,
    AST_EXCEPT_CLAUSE_FINAL,
} ast_type_t;

typedef struct _ast_type_ {
    ast_type_t type;
    const char* fname;
    int col;
    int line;
} ast_type;

/*
 *  module
 *      : module_body
 *      ;
 */
typedef struct _ast_module_ {
    ast_type type;
} ast_module;
struct _ast_module_* create_module();

/*
 *  module_element
 *      : namespace_element
 *      | import_statement
 *      | entry_definition
 *      ;
 */
typedef struct _ast_module_element_ {
    ast_type type;
} ast_module_element;
struct _ast_module_element_* create_module_element();

/*
 *  module_body
 *      : module_element
 *      | module_body module_element
 *      ;
 */
typedef struct _ast_module_body_ {
    ast_type type;
} ast_module_body;
struct _ast_module_body_* create_module_body();

/*
 *  entry_definition
 *      : ENTRY func_block
 *      ;
 */
typedef struct _ast_entry_definition_ {
    ast_type type;
} ast_entry_definition;
struct _ast_entry_definition_* create_entry_definition();

/*
 *  scope
 *      : PUBLIC
 *      | PRIVATE
 *      | PROTECTED
 *      ;
 */
typedef struct _ast_scope_ {
    ast_type type;
} ast_scope;
struct _ast_scope_* create_scope();

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
typedef struct _ast_type_name_ {
    ast_type type;
} ast_type_name;
struct _ast_type_name_* create_type_name();

/*
 *  compound_reference
 *      : compound_reference_element
 *      | compound_reference DOT compound_reference_element
 *      ;
 */
typedef struct _ast_compound_reference_ {
    ast_type type;
} ast_compound_reference;
struct _ast_compound_reference_* create_compound_reference();

/*
 *  compound_reference_element
 *      : compound_name
 *      | func_reference
 *      | array_reference
 *      ;
 */
typedef struct _ast_compound_reference_element_ {
    ast_type type;
} ast_compound_reference_element;
struct _ast_compound_reference_element_* create_compound_reference_element();

/*
 *  compound_name
 *      : SYMBOL
 *      | COMPOUND
 *      ;
 */
typedef struct _ast_compound_name_ {
    ast_type type;
} ast_compound_name;
struct _ast_compound_name_* create_compound_name();

/*
 *  formatted_string
 *      : STRG_CONST
 *      | STRG_CONST OPAREN CPAREN
 *      | STRG_CONST OPAREN expr_list CPAREN
 *      ;
 */
typedef struct _ast_formatted_string_ {
    ast_type type;
} ast_formatted_string;
struct _ast_formatted_string_* create_formatted_string();

/*
 *  func_reference
 *      : compound_name OPAREN CPAREN
 *      | compound_name OPAREN expr_list CPAREN
 *      ;
 */
typedef struct _ast_func_reference_ {
    ast_type type;
} ast_func_reference;
struct _ast_func_reference_* create_func_reference();

/*
 *  array_reference
 *      : compound_name array_reference_list
 *      ;
 */
typedef struct _ast_array_reference_ {
    ast_type type;
} ast_array_reference;
struct _ast_array_reference_* create_array_reference();

/*
 *  array_reference_list
 *      : OBRACE expression CBRACE
 *      | array_reference_list OBRACE expression CBRACE
 *      ;
 */
typedef struct _ast_array_reference_list_ {
    ast_type type;
} ast_array_reference_list;
struct _ast_array_reference_list_* create_array_reference_list();

/*
 *  import_statement
 *      : IMPORT compound_name
 *      | IMPORT compound_name AS SYMBOL
 *      ;
 */
typedef struct _ast_import_statement_ {
    ast_type type;
} ast_import_statement;
struct _ast_import_statement_* create_import_statement();

/*
 *  namespace_definition
 *      : NAMESPACE SYMBOL OBLOCK namespace_block CBLOCK
 *      ;
 */
typedef struct _ast_namespace_definition_ {
    ast_type type;
} ast_namespace_definition;
struct _ast_namespace_definition_* create_namespace_definition();

/*
 *  namespace_block
 *      : namespace_element
 *      | namespace_block namespace_element
 *      ;
 */
typedef struct _ast_namespace_block_ {
    ast_type type;
} ast_namespace_block;
struct _ast_namespace_block_* create_namespace_block();

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
typedef struct _ast_namespace_element_ {
    ast_type type;
} ast_namespace_element;
struct _ast_namespace_element_* create_namespace_element();

/*
 *  class_definition
 *      : CLASS SYMBOL class_parameters class_block
 *      ;
 */
typedef struct _ast_class_definition_ {
    ast_type type;
} ast_class_definition;
struct _ast_class_definition_* create_class_definition();

/*
 *  class_parameters
 *      : %empty
 *      | OPAREN CPAREN
 *      | OPAREN compound_name CPAREN
 *      ;
 */
typedef struct _ast_class_parameters_ {
    ast_type type;
} ast_class_parameters;
struct _ast_class_parameters_* create_class_parameters();

/*
 *  class_block
 *      : OBLOCK CBLOCK
 *      | OBLOCK class_body CBLOCK
 *      ;
 */
typedef struct _ast_class_block_ {
    ast_type type;
} ast_class_block;
struct _ast_class_block_* create_class_block();

/*
 *  class_body
 *      : class_body_element
 *      | class_body class_body_element
 *      ;
 */
typedef struct _ast_class_body_ {
    ast_type type;
} ast_class_body;
struct _ast_class_body_* create_class_body();

/*
 *  class_body_element
 *      : var_declaration
 *      | func_declaration
 *      | scope
 *      ;
 */
typedef struct _ast_class_body_element_ {
    ast_type type;
} ast_class_body_element;
struct _ast_class_body_element_* create_class_body_element();

/*
 *  var_declaration
 *      : type_name SYMBOL
 *      ;
 */
typedef struct _ast_var_declaration_ {
    ast_type type;
} ast_var_declaration;
struct _ast_var_declaration_* create_var_declaration();

/*
 *  func_declaration
 *      : type_name SYMBOL func_decl_parms
 *      | CREATE func_decl_parms
 *      | DESTROY
 *      ;
 */
typedef struct _ast_func_declaration_ {
    ast_type type;
} ast_func_declaration;
struct _ast_func_declaration_* create_func_declaration();

/*
 *  func_decl_parms
 *      : OPAREN CPAREN
 *      | OPAREN func_decl_parms_list CPAREN
 *      ;
 */
typedef struct _ast_func_decl_parms_ {
    ast_type type;
} ast_func_decl_parms;
struct _ast_func_decl_parms_* create_func_decl_parms();

/*
 *  func_decl_parms_list
 *      : func_decl_parms_elem
 *      | func_decl_parms_list COMMA func_decl_parms_elem
 *      ;
 */
typedef struct _ast_func_decl_parms_list_ {
    ast_type type;
} ast_func_decl_parms_list;
struct _ast_func_decl_parms_list_* create_func_decl_parms_list();

/*
 *  func_decl_parms_elem
 *      : type_name SYMBOL
 *      ;
 */
typedef struct _ast_func_decl_parms_elem_ {
    ast_type type;
} ast_func_decl_parms_elem;
struct _ast_func_decl_parms_elem_* create_func_decl_parms_elem();

/*
 *  bool_literal
 *      : TRUE
 *      | FALSE
 *      ;
 */
typedef struct _ast_bool_literal_ {
    ast_type type;
} ast_bool_literal;
struct _ast_bool_literal_* create_bool_literal();

/*
 *  primary
 *      : compound_reference
 *      | const_expression
 *      | OPAREN expression CPAREN
 *      ;
 */
typedef struct _ast_primary_ {
    ast_type type;
} ast_primary;
struct _ast_primary_* create_primary();

/*
 *  const_expression
 *      : formatted_string
 *      | bool_literal
 *      | FLOAT_CONST
 *      | INT_CONST
 *      | UNSIGNED_CONST
 *      ;
 */
typedef struct _ast_const_expression_ {
    ast_type type;
} ast_const_expression;
struct _ast_const_expression_* create_const_expression();

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
typedef struct _ast_expression_ {
    ast_type type;
} ast_expression;
struct _ast_expression_* create_expression();

/*
 *  cast_expr
 *      : OPOINT type_name CPOINT expression
 *      ;
 */
typedef struct _ast_cast_expr_ {
    ast_type type;
} ast_cast_expr;
struct _ast_cast_expr_* create_cast_expr();

/*
 *  expr_list
 *      : expression
 *      | expr_list COMMA expression
 *      ;
 */
typedef struct _ast_expr_list_ {
    ast_type type;
} ast_expr_list;
struct _ast_expr_list_* create_expr_list();

/*
 *  member
 *      : SYMBOL COLON
 *      ;
 */
typedef struct _ast_member_ {
    ast_type type;
} ast_member;
struct _ast_member_* create_member();

/*
 *  func_definition
 *      : type_name member SYMBOL func_decl_parms func_block
 *      ;
 */
typedef struct _ast_func_definition_ {
    ast_type type;
} ast_func_definition;
struct _ast_func_definition_* create_func_definition();

/*
 *  ctor_definition
 *      : member OPAREN func_decl_parms CPAREN func_block
 *      ;
 */
typedef struct _ast_ctor_definition_ {
    ast_type type;
} ast_ctor_definition;
struct _ast_ctor_definition_* create_ctor_definition();

/*
 *  dtor_definition
 *      : member DESTROY func_block
 *      ;
 */
typedef struct _ast_dtor_definition_ {
    ast_type type;
} ast_dtor_definition;
struct _ast_dtor_definition_* create_dtor_definition();

/*
 *  func_block
 *      : OBLOCK CBLOCK
 *      | OBLOCK func_content CBLOCK
 *      ;
 */
typedef struct _ast_func_block_ {
    ast_type type;
} ast_func_block;
struct _ast_func_block_* create_func_block();

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
typedef struct _ast_assignment_oper_ {
    ast_type type;
} ast_assignment_oper;
struct _ast_assignment_oper_* create_assignment_oper();

/*
 *  assignment
 *      : assignment_oper expression
 *      ;
 */
typedef struct _ast_assignment_ {
    ast_type type;
} ast_assignment;
struct _ast_assignment_* create_assignment();

/*
 *  data_definition
 *      : var_declaration
 *      | var_declaration assignment
 *      ;
 */
typedef struct _ast_data_definition_ {
    ast_type type;
} ast_data_definition;
struct _ast_data_definition_* create_data_definition();

/*
 *  func_content
 *      : func_content_elem
 *      | func_content func_content_elem
 *      ;
 */
typedef struct _ast_func_content_ {
    ast_type type;
} ast_func_content;
struct _ast_func_content_* create_func_content();

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
typedef struct _ast_func_content_elem_ {
    ast_type type;
} ast_func_content_elem;
struct _ast_func_content_elem_* create_func_content_elem();

/*
 *  inline_block
 *      : IBEGIN STRG_CONST IEND
 *      ;
 */
typedef struct _ast_inline_block_ {
    ast_type type;
} ast_inline_block;
struct _ast_inline_block_* create_inline_block();

/*
 *  print_statement
 *      : PRINT
 *      | PRINT OPAREN CPAREN
 *      | PRINT OPAREN formatted_string CPAREN
 *      ;
 */
typedef struct _ast_print_statement_ {
    ast_type type;
} ast_print_statement;
struct _ast_print_statement_* create_print_statement();

/*
 *  break_statement
 *      : BREAK
 *      ;
 */
typedef struct _ast_break_statement_ {
    ast_type type;
} ast_break_statement;
struct _ast_break_statement_* create_break_statement();

/*
 *  cont_statement
 *      : CONTINUE
 *      ;
 */
typedef struct _ast_cont_statement_ {
    ast_type type;
} ast_cont_statement;
struct _ast_cont_statement_* create_cont_statement();

/*
 *  trace_statement
 *      : TRACE
 *      | TRACE OPAREN CPAREN
 *      | TRACE OPAREN formatted_string CPAREN
 *      ;
 */
typedef struct _ast_trace_statement_ {
    ast_type type;
} ast_trace_statement;
struct _ast_trace_statement_* create_trace_statement();

/*
 *  yield_statement
 *      : YIELD OPAREN SYMBOL CPAREN
 *      ;
 */
typedef struct _ast_yield_statement_ {
    ast_type type;
} ast_yield_statement;
struct _ast_yield_statement_* create_yield_statement();

/*
 *  exit_statement
 *      : EXIT OPAREN expression CPAREN
 *      ;
 */
typedef struct _ast_exit_statement_ {
    ast_type type;
} ast_exit_statement;
struct _ast_exit_statement_* create_exit_statement();

/*
 *  return_statement
 *      : RETURN
 *      | RETURN OPAREN CPAREN
 *      | RETURN OPAREN expression CPAREN
 *      ;
 */
typedef struct _ast_return_statement_ {
    ast_type type;
} ast_return_statement;
struct _ast_return_statement_* create_return_statement();

/*
 *  raise_statement
 *      : RAISE OPAREN compound_name CPAREN
 *      ;
 */
typedef struct _ast_raise_statement_ {
    ast_type type;
} ast_raise_statement;
struct _ast_raise_statement_* create_raise_statement();

/*
 *  if_else_clause
 *      : if_clause
 *      | if_clause else_clause_list
 *      | if_clause else_clause_list else_clause_final
 *      ;
 */
typedef struct _ast_if_else_clause_ {
    ast_type type;
} ast_if_else_clause;
struct _ast_if_else_clause_* create_if_else_clause();

/*
 *  if_clause
 *      : IF OPAREN expression CPAREN func_block
 *      ;
 */
typedef struct _ast_if_clause_ {
    ast_type type;
} ast_if_clause;
struct _ast_if_clause_* create_if_clause();

/*
 *  else_clause
 *      : ELSE OPAREN expression CPAREN func_block
 *      ;
 */
typedef struct _ast_else_clause_ {
    ast_type type;
} ast_else_clause;
struct _ast_else_clause_* create_else_clause();

/*
 *  else_clause_list
 *      : else_clause
 *      | else_clause_list else_clause
 *      ;
 */
typedef struct _ast_else_clause_list_ {
    ast_type type;
} ast_else_clause_list;
struct _ast_else_clause_list_* create_else_clause_list();

/*
 *  else_clause_final
 *      : ELSE OPAREN CPAREN func_block
 *      | ELSE func_block
 *      ;
 */
typedef struct _ast_else_clause_final_ {
    ast_type type;
} ast_else_clause_final;
struct _ast_else_clause_final_* create_else_clause_final();

/*
 *  while_clause
 *      : WHILE OPAREN expression CPAREN func_block
 *      ;
 */
typedef struct _ast_while_clause_ {
    ast_type type;
} ast_while_clause;
struct _ast_while_clause_* create_while_clause();

/*
 *  do_clause
 *      : DO func_block WHILE OPAREN expression CPAREN
 *      ;
 */
typedef struct _ast_do_clause_ {
    ast_type type;
} ast_do_clause;
struct _ast_do_clause_* create_do_clause();

/*
 *  for_clause
 *      : FOR OPAREN SYMBOL IN compound_reference CPAREN func_block
 *      | FOR OPAREN SYMBOL IN expression TO expression CPAREN func_block
 *      ;
 */
typedef struct _ast_for_clause_ {
    ast_type type;
} ast_for_clause;
struct _ast_for_clause_* create_for_clause();

/*
 *  switch_case_clause
 *      : switch_clause case_clause_list case_clause_final
 *      ;
 */
typedef struct _ast_switch_case_clause_ {
    ast_type type;
} ast_switch_case_clause;
struct _ast_switch_case_clause_* create_switch_case_clause();

/*
 *  switch_clause
 *      : SWITCH OPAREN expression CPAREN OBLOCK
 *      ;
 */
typedef struct _ast_switch_clause_ {
    ast_type type;
} ast_switch_clause;
struct _ast_switch_clause_* create_switch_clause();

/*
 *  case_clause
 *      : CASE OPAREN const_expression CPAREN func_block
 *      ;
 */
typedef struct _ast_case_clause_ {
    ast_type type;
} ast_case_clause;
struct _ast_case_clause_* create_case_clause();

/*
 *  case_clause_list
 *      : case_clause
 *      | case_clause_list case_clause
 *      ;
 */
typedef struct _ast_case_clause_list_ {
    ast_type type;
} ast_case_clause_list;
struct _ast_case_clause_list_* create_case_clause_list();

/*
 *  case_clause_final
 *      : CBLOCK
 *      | DEFAULT func_block CBLOCK
 *      ;
 */
typedef struct _ast_case_clause_final_ {
    ast_type type;
} ast_case_clause_final;
struct _ast_case_clause_final_* create_case_clause_final();

/*
 *  try_except_clause
 *      : try_clause except_clause_list except_clause_final
 *      ;
 */
typedef struct _ast_try_except_clause_ {
    ast_type type;
} ast_try_except_clause;
struct _ast_try_except_clause_* create_try_except_clause();

/*
 *  try_clause
 *      : TRY func_block
 *      ;
 */
typedef struct _ast_try_clause_ {
    ast_type type;
} ast_try_clause;
struct _ast_try_clause_* create_try_clause();

/*
 *  except_clause
 *      : EXCEPT OPAREN compound_name CPAREN func_block
 *      ;
 */
typedef struct _ast_except_clause_ {
    ast_type type;
} ast_except_clause;
struct _ast_except_clause_* create_except_clause();

/*
 *  except_clause_list
 *      : except_clause
 *      | except_clause_list except_clause
 *      ;
 */
typedef struct _ast_except_clause_list_ {
    ast_type type;
} ast_except_clause_list;
struct _ast_except_clause_list_* create_except_clause_list();

/*
 *  except_clause_final
 *      : EXCEPT OPAREN CPAREN func_block
 *      | EXCEPT func_block
 *      ;
 */
typedef struct _ast_except_clause_final_ {
    ast_type type;
} ast_except_clause_final;
struct _ast_except_clause_final_* create_except_clause_final();


#define TYPEOF(p) ((ast_type*)p)->type;

#endif /* _AST_H */


/*
%type <nterm> module
%type <nterm> module_element
%type <nterm> module_body
%type <nterm> entry_definition
%type <nterm> scope
%type <nterm> type_name
%type <nterm> compound_reference
%type <nterm> compound_reference_element
%type <nterm> compound_name
%type <nterm> formatted_string
%type <nterm> func_reference
%type <nterm> array_reference
%type <nterm> array_reference_list
%type <nterm> import_statement
%type <nterm> namespace_definition
%type <nterm> namespace_block
%type <nterm> namespace_element
%type <nterm> class_definition
%type <nterm> class_parameters
%type <nterm> class_block
%type <nterm> class_body
%type <nterm> class_body_element
%type <nterm> var_declaration
%type <nterm> func_declaration
%type <nterm> func_decl_parms
%type <nterm> func_decl_parms_list
%type <nterm> func_decl_parms_elem
%type <nterm> bool_literal
%type <nterm> primary
%type <nterm> const_expression
%type <nterm> expression
%type <nterm> cast_expr
%type <nterm> expr_list
%type <nterm> member
%type <nterm> func_definition
%type <nterm> ctor_definition
%type <nterm> dtor_definition
%type <nterm> func_block
%type <nterm> assignment_oper
%type <nterm> assignment
%type <nterm> data_definition
%type <nterm> func_content
%type <nterm> func_content_elem
%type <nterm> inline_block
%type <nterm> print_statement
%type <nterm> break_statement
%type <nterm> cont_statement
%type <nterm> trace_statement
%type <nterm> yield_statement
%type <nterm> exit_statement
%type <nterm> return_statement
%type <nterm> raise_statement
%type <nterm> if_else_clause
%type <nterm> if_clause
%type <nterm> else_clause
%type <nterm> else_clause_list
%type <nterm> else_clause_final
%type <nterm> while_clause
%type <nterm> do_clause
%type <nterm> for_clause
%type <nterm> switch_case_clause
%type <nterm> switch_clause
%type <nterm> case_clause
%type <nterm> case_clause_list
%type <nterm> case_clause_final
%type <nterm> try_except_clause
%type <nterm> try_clause
%type <nterm> except_clause
%type <nterm> except_clause_list
%type <nterm> except_clause_final
*/
