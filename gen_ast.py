'''
This module parses the grammer file named "parse.y" and generates all data
structures and functions required to implement building the AST for the input
file. Traversing the AST is left for the developer to implement.
'''
import re
from pprint import pprint as pp

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
                                type == 'int64_t'
                            elif x[1] == '<unum>':
                                type == 'uint64_t'
                            elif x[1] == '<fnum>':
                                type == 'double'
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
    Return a list of unique symbols that are found in all of the rules
    associated with this non-terminal symbol.
    '''
    tmp = {}
    for line in fp:
        if line.strip() == ';':
            break
        elif (line.strip()[0] == ':' or line.strip()[0] == '|') \
                    and not '%empty' in line:
            x = line.strip().split()
            for elem in x[1:]:
                if '{' in elem:
                    break
                else:
                    if elem in tokens:
                        if tokens[elem] != 'terminal':
                            tmp[elem] = ""
                    else:
                        tmp[elem] = ""

    return list(tmp.keys())

def mk_ds_names(rules):
    '''
    Scan the rules dictionary and generate data structure name for each rule.
    '''
    for item in rules:
        rules[item]['name'] = "ast_%s_t"%(item)

def read_rules(tokens):
    '''
    Isolate the non-terminal definition and the hints associated with it.
    Then read the rule elements and store those in the dictionary.

    Returns a dictionary of all of the rules that were found in the grammar.
    '''
    rules = {}
    with open("parser.y", "r") as fp:
        for line in fp:
            if '%%' in line:
                for item in fp:
                    if '%%' in item:
                        break;
                    else:
                        m = re.findall(r'^(\w+)(\s*/\*\s*([:\w\s]+)\*/)?', item)
                        if len(m) != 0:
                            name = m[0][0]
                            rules[name] = {}
                            rules[name]['elem'] = read_rule_elem(fp, tokens)
                            rules[name]['hint'] = []
                            if len(m[0][2]) > 1:
                                a = m[0][2].split()
                                if a[0].lower() == "hint:":
                                    for h in a[1:]:
                                        rules[name]['hint'].append(h)
                break

    mk_ds_names(rules)
    return rules

def emit_nterms(rules):

    with open("nterms.txt", 'w') as fp:
        for item in rules:
            fp.write("%%type <nterm> %s\n"%(item))

def emit_enum(fp, data):

    fp.write('typedef enum {\n')
    for item in data['rules']:
        fp.write('    AST_%s,\n'%(item))
    fp.write('} ast_type_t;\n\n')

def emit_ds_items(fp, name, data):
    '''
    Emit the items in a data structre.
    '''
    for item in data['rules'][name]['elem']:
        if item in data['tokens']:
            fp.write('    %s %s;\n'%(data['tokens'][item], item))
        else:
            fp.write('    struct ast_%s_t* %s;\n'%(item, item))


def emit_all_ds(fp, data):
    '''
    Emit the complete data structures for the AST tree.
    '''
    for item in data['rules']:
        x = data['rules'][item]
        if len(x['hint']) > 0:
            fp.write('/* hints: %s */\n'%(', '.join(x['hint'])))
        else:
            fp.write('/* hints: NONE */\n')
        fp.write('typedef struct _%s_ {\n'%(x['name']))
        fp.write('    ast_type_t type;\n')
        emit_ds_items(fp, item, data)
        fp.write('} %s;\n\n'%(x['name']))

def emit_ast_h(data):
    '''
    Emit the AST data structures and prototypes to 'ast.h'
    '''
    with open('ast.h', 'w') as fp:
        fp.write('/*\n')
        fp.write('   This file is generated at build time.\n')
        fp.write('       -- DO NOT EDIT THIS FILE --\n')
        fp.write(' */\n\n')
        fp.write('#ifndef _AST_H\n')
        fp.write('#define _AST_H\n\n')

        emit_enum(fp, data)
        emit_all_ds(fp, data)

        fp.write('\n#endif /* _AST_H */\n\n')

def emit_ast_c(data):
    '''
    Emit the AST function definitions to 'ast.c'
    '''
    with open('ast.c', 'w') as fp:
        fp.write('/*\n')
        fp.write('   This file is generated at build time.\n')
        fp.write('       -- DO NOT EDIT THIS FILE --\n')
        fp.write(' */\n\n')
        fp.write('#include <stdio.h>\n\n')
        fp.write('#include "ast.h"\n')
        fp.write('#include "mem.h"\n')
        fp.write('#include "ptrlst.h"\n')

if __name__ == '__main__':

    tokens = read_tokens()
    pp(tokens)
    rules = read_rules(tokens)
    pp(rules)
    data = {'tokens': tokens, 'rules': rules}

    emit_nterms(rules)
    emit_ast_h(data)
    emit_ast_c(data)

