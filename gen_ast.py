#!/usr/bin/env python3
'''

This creates boilerplate code for the AST.

DO NOT RUN THIS
without first making backups of the existing code.

'''
from pprint import pprint as pp
import os
import re

def read_tokens():
    '''
    Return a dictionary of token names where the value is a string
    representing the type of the token. If the token has no type then
    the type name is "terminal".
    '''
    tokens = {}
    with open("parser.y", "r") as fp:
        for line in fp:
            if '%}' in line:
                for item in fp:
                    if '%%' in item:
                        break;
                    elif '%token' in item:
                        type = ''
                        x = item.split()
                        if x[1][0] == '<':
                            if x[1] == '<str>':
                                type = 'const char*'
                            elif x[1] == '<inum>':
                                type = 'int64_t'
                            elif x[1] == '<unum>':
                                type = 'uint64_t'
                            elif x[1] == '<fnum>':
                                type = 'double'
                            elif x[1] == '<symbol>':
                                type = 'int'
                        else:
                            type = 'terminal'
                        for thing in x:
                            if not '%' in thing and not '<' in thing:
                                tokens[thing] = type
                break

    return tokens

def read_rule_elem(fp, tokens):
    '''
    Filter each line and if it starts with a ':' or a '|' then its a rule. Make
    a list of all of these lines, stripped, and return the list.
    '''
    arr = []
    for line in fp:
        s = line.strip()
        if len(s) == 0:
            break
        #print(s)
        if s[0] == ':' or s[0] == '|':
            x = s.split()
            p = ''
            for item in x:
                #pp(item)
                if item[0] == '{':
                    break
                elif item[0] != ':' and item[0] != '|':
                    p += ' '
                    p += item

            arr.append(p.strip().split())
            #arr = arr + p.strip().split()
        #print(arr)
    return arr #list(set(arr))

def read_rules(tokens):
    '''
    Read all of the rules and return a dictionary in which the name of the rule
    is the name of the entry and all of the raw rules are given as an array of
    strings.
    '''
    rules = {}
    with open("parser.y", "r") as fp:
        for line in fp:
            m = re.findall(r'^[%]{2}$', line)
            if len(m) != 0:
                for item in fp:
                    m = re.findall(r'^[%]{2}$', item)
                    if len(m) != 0:
                        break
                    else:
                        x = re.findall(r'^\w+$', item)
                        if len(x) != 0:
                            rules[x[0]] = read_rule_elem(fp, tokens)
    return rules

def emit_ast_header(data):
    if os.path.exists("ast.h"):
        if os.path.exists("ast.h.bak"):
            os.remove("ast.h.bak")
        os.rename("ast.h", "ast.h.bak")

    with open('ast.h', 'w') as fp:
        fp.write("#ifndef _AST_H\n")
        fp.write("#define _AST_H\n")

        fp.write("\n")
        fp.write("typedef enum {\n")
        #for item in data['tokens']:
        #    if data['tokens'][item] != 'terminal':
        #        fp.write("    AST_%s,\n"%(item))
        for item in data['rules']:
            fp.write("    AST_%s,\n"%(item.upper()))
        fp.write("} ast_type_t;\n")

        fp.write("\n")
        fp.write("typedef struct _ast_type_ {\n")
        fp.write("    ast_type_t type;\n")
        fp.write("    const char* fname;\n")
        fp.write("    int col;\n")
        fp.write("    int line;\n")
        fp.write("} ast_type;\n")

        fp.write("\n")
        for item in data['rules']:
            fp.write("/*\n")
            fp.write(" *  %s\n"%(item))
            s = ':'
            for line in data['rules'][item]:
                fp.write(" *      %s %s\n"%(s, ' '.join(line)))
                s = '|'
            fp.write(" *      ;\n */\n")
            fp.write("typedef struct _ast_%s_ {\n"%(item))
            fp.write("    ast_type type;\n")
            fp.write("} ast_%s;\n"%(item))
            fp.write("struct _ast_%s_* create_%s();\n\n"%(item, item))

        fp.write("\n")
        fp.write("#define TYPEOF(p) ((ast_type*)p)->type;\n\n")
        fp.write("#endif /* _AST_H */\n\n")
        fp.write("\n")
        fp.write("/*\n")
        for item in data['rules']:
            fp.write("%%type <nterm> %s\n"%(item))
        fp.write("*/\n")

def emit_ast_src():
    if os.path.exists("ast.c"):
        if os.path.exists("ast.c.bak"):
            os.remove("ast.c.bak")
        os.rename("ast.c", "ast.c.bak")

    with open('ast.c', 'w') as fp:
        fp.write("#include <stdio.h>\n")
        fp.write("#include <stdint.h>\n\n")
        fp.write("#include \"ast.h\"\n")
        fp.write("#include \"mem.h\"\n")
        fp.write("#include \"str.h\"\n")
        fp.write("#include \"log.h\"\n")
        fp.write("#include \"scanner.h\"\n\n")
        for item in data['rules']:
            fp.write("/*\n")
            fp.write(" *  %s\n"%(item))
            s = ':'
            for line in data['rules'][item]:
                fp.write(" *      %s %s\n"%(s, ' '.join(line)))
                s = '|'
            fp.write(" *      ;\n */\n")
            fp.write("struct _ast_%s_* create_%s() {\n\n"%(item, item))
            fp.write("    TRACE();\n")
            fp.write("    struct _ast_%s_* ptr = _ALLOC_T(struct _ast_%s_);\n"%(item, item))
            fp.write("    ptr->type.type = AST_%s;\n"%(item.upper()))
            fp.write("    ptr->type.col = get_col_no();\n")
            fp.write("    ptr->type.line = get_line_no();\n")
            fp.write("    ptr->type.fname = get_file_name();\n\n\n")
            fp.write("    return ptr;\n")
            fp.write("}\n\n")


if __name__ == '__main__':

    t = read_tokens()
    r = read_rules(t)
    data = {'tokens':t, 'rules':r}
    #pp(data)

    emit_ast_header(data)
    emit_ast_src()

    print("%d tokens and %d rules"%(len(data['tokens']), len(data['rules'])))
