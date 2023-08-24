#! /usr/bin/env python3
import re
from pprint import pprint as pp

# def generate_types():
#     # This generates the symbol names for the AST from the parser.c file.
#     with open("ast_types.h", "w") as ofp:
#         ofp.write("/*\n  This file is generated at build time.\n")
#         ofp.write("    ---- DO NOT EDIT ----\n */\n")
#         ofp.write("#ifndef _AST_TYPES_H\n")
#         ofp.write("#define _AST_TYPES_H\n\n")
#         with open("parser.c", "r") as ifp:
#             for s in ifp:
#                 if "enum yysymbol_kind_t" in s:
#                     ofp.write("enum ast_node_type_t\n")
#                     for p in ifp:
#                         if "};" in p:
#                             ofp.write(p)
#                             break
#                         else:
#                             ofp.write(p.replace("YYSYMBOL_", "AST_TYPE_"))
#                     break
#         ofp.write("\ntypedef enum ast_node_type_t ast_node_type_t;\n\n")
#         ofp.write("#endif /* _AST_TYPES_H */\n\n")

def gen_type_file(terms, nonterms):
    '''
    Generate the AST type definitions file.
    '''
    count = 1000
    with open("ast_types.h", "w") as ofp:
        ofp.write("/*\n  This file is generated at build time.\n")
        ofp.write("    ---- DO NOT EDIT ----\n */\n")
        ofp.write("#ifndef _AST_TYPES_H\n")
        ofp.write("#define _AST_TYPES_H\n\n")
        ofp.write("enum ast_node_type_t {\n")

        ofp.write("\n    /* terminal symbols */\n")
        for s in terms:
            ofp.write("    AST_TYPE_"+s+" = "+str(count)+",\n")
            count = count + 1

        ofp.write("\n    /* non-terminal symbols */\n")
        for s in nonterms:
            ofp.write("    AST_TYPE_"+s+" = "+str(count)+",\n")
            count = count + 1

        ofp.write("}; /* ast_node_type_t */\n")
        ofp.write("\ntypedef enum ast_node_type_t ast_node_type_t;\n\n")
        ofp.write("#endif /* _AST_TYPES_H */\n\n")

def get_symbols():
    '''
    Produce a list of terminal and non-terminal symbols.
    '''
    tflag = True
    terms = []
    nonterms = []

    startre = re.compile("enum yysymbol_kind_t")
    endre = re.compile("};")
    flagre = re.compile("YYSYMBOL_YYACCEPT")
    convre = re.compile("\s+YYSYMBOL_(\w+)")

    with open("parser.c", "r") as ifp:
        for s in ifp:
            if not startre.search(s) is None:
                # throw away the first 5 lines
                count = 0
                for s in ifp:
                    count = count + 1
                    if count > 4:
                        break
                # process the lines
                for s in ifp:
                    if not endre.search(s) is None:
                        break
                    else:
                        if not flagre.search(s) is None:
                            tflag = False
                            # don't save this one
                            continue

                        m = convre.search(s)
                        if not m is None:
                            #print(tflag, m[0])
                            x = m[0].replace("YYSYMBOL_", '').strip()
                            if tflag:
                                terms.append(x)
                            else:
                                nonterms.append(x)

                break

    return (terms, nonterms)

def get_rule_elements(fp, nterms, types):
    '''
    Create a dictionary of the unique elements in a single rule with their
    types.
    '''
    elements = {}
    for s in fp:
        # look for a ';' on a line with nothing else.
        m = re.match(r"^\s+;$", s)
        if not m is None:
            break;
        else:
            p = s.strip()
            #print("this:", p)
            if (p[0] == ":" or p[0] == "|") and not "%empty" in p:
                x = re.sub(r"\{.*\}*", "", s)
                #print(x)
                m = re.findall(r"[\w]+", x.strip())
                #print(m)
                for item in m:
                    if item in types:
                        if types[item] == '<str>':
                            elements[item] = {'type': 'const char*'}
                        elif types[item] == '<symbol>':
                            elements[item] = {'type': 'int'}
                        elif types[item] == '<fnum>':
                            elements[item] = {'type': 'double'}
                        elif types[item] == '<inum>':
                            elements[item] = {'type': 'int64_t'}
                        elif types[item] == '<unum>':
                            elements[item] = {'type': 'uint64_t'}
                        else:
                            elements[item] = {'type': 'void*'}
                    elif item in nterms:
                        elements[item] = {'type': 'non-terminal'}

    #print(elements)
    return elements

def get_rules(fp, nterms, types):
    '''
    Read a single complete rule from the grammar and return it as a dictionary.
    '''
    rules = {}
    for s in fp:
        if not re.match('^%%$', s) is None:
            break;
        else:
            m = re.findall(r'^(\w+)(\s*/\*\s*([:\w\s]+)\*/)?', s)
            if len(m) != 0:
                name = m[0][0]
                rules[name] = {}
                rules[name]['rule'] = get_rule_elements(fp, nterms, types)
                rules[name]['hints'] = []
                if len(m[0][2]) > 1:
                    a = m[0][2].split()
                    if a[0].lower() == "hint:":
                        for h in a[1:]:
                            rules[name]['hints'].append(h)

    return rules

def read_rules(nterms, types):
    '''
    Create a dictionary of the rules that are defined in the grammer that has
    the rule elements as long with their types.
    '''
    with open("parser.y", "r") as ifp:
        for s in ifp:
            if not re.match(r'^%%$', s) is None:
                rules = get_rules(ifp, nterms, types)
                break

    return rules

def get_type_line(line):
    '''
    Parse a type line that was found.
    '''
    rule = {}
    ls = line.replace('%token', '').split()
    for s in ls[1:]:
        rule[s] = ls[0]

    return rule

def get_types(fp):
    '''
    Filter for a single type line.
    '''
    rules = {}
    for s in fp:
        if not re.match(r'^%%$', s) is None:
            # found the end of the section
            break
        else:
            if not re.match(r'^%token\s*<\w+>', s) is None:
                rules = rules | get_type_line(s)
            #break

    return rules

def read_types():
    '''
    Read the types of the terminal symbols and return them as a dictionary.
    '''
    types = {}
    # starts with a '%}' and ends with a '%%'
    with open("parser.y", "r") as ifp:
        for s in ifp:
            if not re.match(r'^%}$', s) is None:
                # found the section
                types = get_types(ifp)
                break

    return types

def gen_nterm_file(nterms):

    with open("nterms.txt", "w") as fp:
        for item in nterms:
            fp.write("%%type <nterm> %s\n"%(item))

def mk_ast_name(name):
    return "ast_{}_t".format(name)

def emit_ast_data_structure(fp, name, rule):
    fp.write("\n/* hints: %s */\n"%(str(rule['hints'])))
    fp.write("typedef struct _%s_ {\n"%(mk_ast_name(name)))
    fp.write("    int type;\n")
    flag = False

    for item in rule['rule']:
        if rule['rule'][item]['type'] == 'non-terminal':
            if 'is_a_list' in rule['hints']:
                if name != item:
                    fp.write("    struct _%s_* %s;\n"%(mk_ast_name(item), item))
            else:
                fp.write("    struct _%s_* %s;\n"%(mk_ast_name(item), item))
        else:
            if 'terminals_only' in rule['hints']:
                if 'combine_all_term' in rule['hints']:
                    if flag == False:
                        fp.write("    %s value;\n"%(rule['rule'][item]['type']))
                        flag = True
                else:
                    fp.write("    %s _%s;\n"%(rule['rule'][item]['type'], item.lower()))

    fp.write("} %s;\n"%(mk_ast_name(name)))

def gen_ast_data_structures(rules):

    with open("ast_data.h", "w") as fp:
        for item in rules:
            emit_ast_data_structure(fp, item, rules[item])

if __name__ == '__main__':
    (terms, nterms) = get_symbols()
    gen_type_file(terms, nterms)
    gen_nterm_file(nterms)

    type_list = read_types()
    rules = read_rules(nterms, type_list)
    gen_ast_data_structures(rules)

    pp(type_list)
    pp(rules)

# filter for when a rule element has the same name as the rule. It's a list.
# filter for non-terminals that have a type.
