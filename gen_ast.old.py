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

def emit_nterms(fp, rules):

    fp.write('/*\nCopy to token section of the grammar.\n\n')

    for item in rules:
        fp.write("%%type <nterm> %s\n"%(item))
    fp.write(' */\n')

def emit_enum(fp, data):

    fp.write('typedef enum {\n')
    flag = False
    for item in data['rules']:
        if flag:
            fp.write('    AST_%s,\n'%(item))
        else:
            fp.write('    AST_%s = 1000,\n'%(item))
            flag = True
    fp.write('} ast_type_t;\n\n')

def emit_ds_items(fp, name, data):
    '''
    Emit the items in a data structre.
    '''
    stuff = []
    r = data['rules'][name]
    t = data['tokens']

    # check for rhetorical error
    if 'combine_terms' in r['hint'] and 'combine_nterms' in r['hint']:
        print("Invalid hint: Cannot combine both terms and nterms. Please refactor.")
        exit(1)

    # filter out the terminal symbols and replace with a single int var
    if 'combine_terms' in r['hint']:
        for item in r['elem']:
            if not item in t:
                stuff.append('struct ast_%s_t* %s;'%(item, item))
        stuff.append("%s terms;"%(data['tokens'][item]))
    else:
        for item in r['elem']:
            if item in t:
                stuff.append('//%s %s;'%(data['tokens'][item], item))

    # filter out the non-terminal symbols and replace with a single void* var
    if 'combine_nterms' in r['hint']:
        for item in r['elem']:
            if not item in data['rules']:
                stuff.append('%s %s;'%(data['tokens'][item], item))
        if 'list_element' in r['hint']:
            stuff.append('struct _ast_%s_t_* nterms;'%(name))
        else:
            stuff.append('void* nterms;')
    elif not 'is_list' in r['hint']:
        for item in r['elem']:
            if not item in t:
                stuff.append('struct _ast_%s_t_* %s;'%(item, item))

    if 'is_list' in r['hint'] and 'list_element' in r['hint']:
        print("Invalid hint: Cannot combine both a list and a list element. Please refactor.")
        exit(1)

    # note that a list can only contain 2 rules and the second rule is the list rule.
    if 'is_list' in r['hint']:
        stuff.append('struct _ast_%s_t_* first;'%(r['elem'][0]))
        stuff.append('struct _ast_%s_t_* last;'%(r['elem'][0]))
    elif 'list_element' in r['hint']:
        stuff.append('struct _ast_%s_t_* next;'%(name))

    for item in stuff:
        fp.write('    %s\n'%(item))

    data['rules'][name]['ds'] = stuff

def emit_protos(fp, name, data):

    r = data['rules'][name]
    t = data['tokens']
    fp.write('struct _ast_%s_t_* create_%s();\n'%(name, name))
    if 'is_list' in r['hint']:
        fp.write('void add_%s(struct _ast_%s_t_* lst, struct _ast_%s_t_* elem);\n'\
                    %(name, r['elem'][1], r['elem'][0]))
    fp.write('\n')

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
        fp.write('} %s;\n'%(x['name']))
        emit_protos(fp, item, data)


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
        fp.write('#include <stdint.h>\n\n')
        emit_enum(fp, data)
        #emit_all_ds(fp, data)

        fp.write('\n#define TYPEOF(p) (*((ast_type_t*)(p)))\n\n')

        emit_nterms(fp, data['rules'])

        fp.write('\n#endif /* _AST_H */\n\n')

def emit_create(fp, name, data):
    '''
    Emit a single "create" function.
    '''
    r = data['rules'][name]

    fp.write('/*\n')
    fp.write('{\n            $$ = (void*)create_%s();\n'%(name))
    for item in r['ds']:
        x = item.split()
        fp.write('           ((struct _ast_%s_t_*)$$)->%s = $1;\n'%(name, x[-1].replace(';', '')))
    fp.write('        }\n */\n')

    fp.write('struct _ast_%s_t_* create_%s() {\n\n'%(name, name))
    fp.write('    TRACE();\n')
    fp.write('    struct _ast_%s_t_* ptr = _ALLOC_T(struct _ast_%s_t_);\n'%(name, name))
    fp.write('    ptr->type = AST_%s;\n\n'%(name))
    fp.write('    return ptr;\n')
    fp.write('}\n\n')

def emit_add(fp, name, data):
    '''
    Emit a single "add" function.
    '''
    r = data['rules'][name]

    fp.write('/*\n')
    fp.write('    add_%s((struct _ast_%s_t_*)$$, $1);\n'%(name, name))
    fp.write(' */\n')

    fp.write('void add_%s(struct _ast_%s_t_* lst, struct _ast_%s_t_* elem) {\n\n'\
                    %(name, r['elem'][1], r['elem'][0]))
    fp.write('    assert(lst != NULL);\n')
    fp.write('    assert(elem != NULL);\n\n')
    fp.write('    TRACE();\n')
    fp.write('    if(lst->first == NULL)\n')
    fp.write('        lst->first = elem;\n')
    fp.write('    else\n')
    fp.write('        lst->last->next = elem;\n')
    fp.write('    lst->last = elem;\n\n')
    fp.write('    elem->next = NULL;\n')
    fp.write('}\n\n')

def emit_ast_c(data):
    '''
    Emit the AST function definitions to 'ast.c'
    '''
    with open('ast.c', 'w') as fp:
        fp.write('/*\n')
        fp.write('   This file is generated at build time.\n')
        fp.write('       -- DO NOT EDIT THIS FILE --\n')
        fp.write(' */\n\n')
        fp.write('#include <stdio.h>\n')
        fp.write('#include <assert.h>\n\n')
        fp.write('#include "ast.h"\n')
        fp.write('#include "log.h"\n')
        fp.write('#include "mem.h"\n\n')

        # for item in data['rules']:
        #     emit_create(fp, item, data)
        #     if 'is_list' in data['rules'][item]['hint']:
        #         emit_add(fp, item, data)

if __name__ == '__main__':

    tokens = read_tokens()
    rules = read_rules(tokens)
    data = {'tokens': tokens, 'rules': rules}

    emit_ast_h(data)
    emit_ast_c(data)

    pp(data)

