
from pprint import pprint as pp
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

            arr.append(p.strip())
        #print(arr)
    return arr

def read_rules(tokens):
    '''
    Read all of the rules and return a dictionary in which the name of the rule
    is the name of the entry and all of the raw rules are given as an array of
    strings.
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
                            rules[name]['emit'] = []
                            if len(m[0][2]) > 1:
                                a = m[0][2].split()
                                if a[0].lower() == "emit:":
                                    for h in a[1:]:
                                        rules[name]['emit'].append(h)
                break

    #mk_ds_names(rules)
    return rules

def emit_ast_header():
    with open('ast.h', 'w') as fp:
        fp.write("\n")

def emit_ast_src():
    with open('ast.c', 'w') as fp:
        fp.write("#include <stdio.h>\n")

if __name__ == '__main__':

    t = read_tokens()
    r = read_rules(t)
    pp(r)

    emit_ast_header()
    emit_ast_src()
