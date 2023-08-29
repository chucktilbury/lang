%{

#include "str.h"
#include "mem.h"
#include "parser.h"

static STR_T string = NULL;

typedef struct _file_stack_ {
    STR_T fname;
    int line;
    int col;
    FILE* fptr;
    YY_BUFFER_STATE buffer;
    struct _file_stack_* next;
} FileStack;

#define MAX_INCL 15
static FileStack* fstack = NULL;
static int incl_depth = 0;

int yycolumn = 1;

/* This is executed before every action. */
#define YY_USER_ACTION                                                   \
  fstack->line = prev_yylineno; fstack->col = yycolumn;                  \
  if (yylineno == prev_yylineno) yycolumn += yyleng;                     \
  else {                                                                 \
    for (yycolumn = 1; yytext[yyleng - yycolumn] != '\n'; ++yycolumn) {} \
    prev_yylineno = yylineno;                                            \
  }

%}

/* state definitions */
%x SQUOTES
%x DQUOTES

%option noinput nounput
%option yylineno
%option noyywrap

%%

   int prev_yylineno = yylineno;

"namespace"     { return NAMESPACE; }
"class"         { return CLASS; }
"import"        { return IMPORT; }
"public"        { return PUBLIC; }
"private"       { return PRIVATE; }
"protected"     { return PROTECTED; }
"create"        { return CREATE; }
"destroy"       { return DESTROY; }
    /* types */
"int"           { return INTEGER; }
"integer"       { return INTEGER; }
"unsigned"      { return UNSIGNED; }
"float"         { return FLOAT; }
"strg"          { return STRING; }
"string"        { return STRING; }
"dict"          { return DICT; }
"dictionary"    { return DICT; }
"list"          { return LIST; }
"bool"          { return BOOLEAN; }
"boolean"       { return BOOLEAN; }
"noth"          { return NOTHING; }
"nothing"       { return NOTHING; }
"inline_begin"  { return IBEGIN; }
"inline_end"    { return IEND; }
    /* flow */
"entry"         { return ENTRY; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"do"            { return DO; }
    /* for(x in 0 to 50) {} */
"for"           { return FOR; }
"in"            { return IN; }
"to"            { return TO; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"try"           { return TRY; }
"except"        { return EXCEPT; }
"raise"         { return RAISE; }
"return"        { return RETURN; }
"exit"          { return EXIT; }
"switch"        { return SWITCH; }
"default"       { return DEFAULT; }
"case"          { return CASE; }
"yield"         { return YIELD; }
"trace"         { return TRACE; }
"print"         { return PRINT; }
    /* boolean constants */
"true"          { return TRUE; }
"false"         { return FALSE; }
    /* module definitions */
"module"        { return MODULE; }
"executable"    { return EXEC; }
"exec"          { return EXEC; }
"static"        { return STATIC; }
"dynamic"       { return DYNAMIC; }

"=="            { return EQU; }
"equ"           { return EQU; }
"!="            { return NEQU; }
"nequ"          { return NEQU; }
"<="            { return LORE; }
"lore"          { return LORE; }
">="            { return GORE; }
"gore"          { return GORE; }
"!"             { return NOT; }
"not"           { return NOT; }
"|"             { return OR; }
"or"            { return OR; }
"&"             { return AND; }
"and"           { return AND; }

    /* operators */
"+="        { return ADD_ASSIGN; }
"-="        { return SUB_ASSIGN; }
"*="        { return MUL_ASSIGN; }
"/="        { return DIV_ASSIGN; }
"%="        { return MOD_ASSIGN; }
"="         { return ASSIGN; }
"+"         { return ADD; }
"-"         { return SUB; }
"*"         { return MUL; }
"/"         { return DIV; }
"%"         { return MOD; }
"^"         { return POW; }

    /* punctuation */
","         { return COMMA; }
"."         { return DOT; }
"("         { return OPAREN; }
")"         { return CPAREN; }
"{"         { return OBLOCK; }
"}"         { return CBLOCK; }
"["         { return OBRACE; }
"]"         { return CBRACE; }

    /* these are used in comparison and also for casts. */
"<"         { return OPOINT; }
"lt"        { return OPOINT; }
">"         { return CPOINT; }
"gt"        { return CPOINT; }
":"         { return COLON; }

    /* constructed tokens */
[a-zA-Z_][a-zA-Z_0-9]* {
    if(string != NULL) {
        str_clear(string);
        str_cat_str(string, yytext);
    }
    else
        string = str_create(yytext);

    yylval.str = _DUP_STR(str_raw(string));
    return SYMBOL;
}

[0-9]+ {
    yylval.inum = strtol(yytext, NULL, 10);
    return INT_CONST;
}

0[xX][0-9a-fA-F]+ {
    yylval.unum = strtol(yytext, NULL, 16);
    return UNSIGNED_CONST;
}

([0-9]*\.)?[0-9]+([Ee][-+]?[0-9]+)? {
    yylval.fnum = strtod(yytext, NULL);
    return FLOAT_CONST;
}

"\"" {
    if(string == NULL)
        string = str_create(NULL);
    else
        str_clear(string);

    BEGIN(DQUOTES);
}
<DQUOTES>"\"" {

    yylval.str = _DUP_STR(str_raw(string));
    BEGIN(INITIAL);
    return STRG_CONST;
}
<DQUOTES>[^\\\"\n]*  { str_cat_str(string, yytext); }
<DQUOTES>\n   { yylineno++; } /* track line numbers, but strip new line */
<DQUOTES>\\n  { str_cat_char(string, '\n'); }
<DQUOTES>\\r  { str_cat_char(string, '\r'); }
<DQUOTES>\\e  { str_cat_char(string, '\x1b'); }
<DQUOTES>\\t  { str_cat_char(string, '\t'); }
<DQUOTES>\\b  { str_cat_char(string, '\b'); }
<DQUOTES>\\f  { str_cat_char(string, '\f'); }
<DQUOTES>\\v  { str_cat_char(string, '\v'); }
<DQUOTES>\\\\ { str_cat_char(string, '\\'); }
<DQUOTES>\\\" { str_cat_char(string, '\"'); }
<DQUOTES>\\\' { str_cat_char(string, '\''); }
<DQUOTES>\\\? { str_cat_char(string, '\?'); }
<DQUOTES>\\.  { str_cat_char(string, yytext[1]); }
<DQUOTES>\\[xX][0-9a-fA-F]{1,3} {
    str_cat_char(string, (char)strtol(yytext + 2, 0, 16));
}

    /* single quoted strings are absolute literals */
\'  {
    if(string == NULL)
        string = str_create(NULL);
    else
        str_clear(string);

    BEGIN(SQUOTES);
}
<SQUOTES>\' {
    yylval.str = _DUP_STR(str_raw(string));
    BEGIN(INITIAL);
    return STRG_CONST;
}
<SQUOTES>[^\\'\n]*  { str_cat_str(string, yytext); }
<SQUOTES>\\.    { str_cat_str(string, yytext); }
<SQUOTES>\n     {
    str_cat_str(string, yytext);
    yylineno++;
} /* don't strip new lines */

    /* ignored tokens */
;.*\n       {} /* comment */
\n          {}
[ \t\f\r]   {}


. {
    fprintf(stderr, "Warning: invalid character ignored: %c (%02X)\n", yytext[0], yytext[0]);
}


<<EOF>> {

    incl_depth--;

    FileStack* tmp = fstack;
    str_destroy(tmp->fname);
    fclose(tmp->fptr);
    fstack = fstack->next;
    _FREE(tmp);

    if(fstack == NULL) {
        yyterminate();
    }
    else {
        yy_delete_buffer(YY_CURRENT_BUFFER);
        yy_switch_to_buffer(fstack->buffer);
    }
}

%%

int open_file(const char *fname) {

    if(incl_depth > MAX_INCL) {
        fprintf(stderr, "FATAL ERROR: Maximum include depth exceeded\n");
        exit(1);
    }
    incl_depth++;

    FileStack* fs = _ALLOC_T(FileStack);
    fs->fname = str_create(fname);
    fs->line = 1;
    fs->col = 1;
    fs->next = NULL;

    // file_name = _copy_str(fname);
    yyin = fopen(fname, "r");
    if(yyin == NULL) {
        fprintf(stderr, "fatal error: cannot open input file: %s: %s\n", fname,
                strerror(errno));
        exit(1);
    }
    fs->fptr = yyin;
    fs->buffer = yy_create_buffer(yyin, YY_BUF_SIZE);
    yy_switch_to_buffer(fs->buffer);

    if(fstack != NULL) {
        fs->next = fstack;
        fstack = fs;
    }
    else
        fstack = fs;

    BEGIN(INITIAL);
    return 0;
}

int get_line_no() {

    if(fstack != NULL)
        return fstack->line;
    else
        return -1;
}

int get_col_no() {

    if(fstack != NULL)
        return fstack->col;
    else
        return -1;
}

const char* get_file_name() {

    if(fstack != NULL)
        return str_raw(fstack->fname);
    else
        return "no file open";
}
