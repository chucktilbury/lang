import re
from pprint import pprint as pp

def read_tokens():

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

def read_rule_elem(fp):

    tmp = {}
    for line in fp:
        if line.strip() == ';':
            break
        elif (line.strip()[0] == ':' or line.strip()[0] == '|') \
                    and not '%empty' in line:
            x = line.strip().split()
            for elem in x[1:]:



def read_rules():

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
                            rules[name]['rule'] = read_rule_elem(fp)
                            rules[name]['hints'] = []
                            if len(m[0][2]) > 1:
                                a = m[0][2].split()
                                if a[0].lower() == "hint:":
                                    for h in a[1:]:
                                        rules[name]['hints'].append(h)
                break

    return rules

if __name__ == '__main__':

    tokens = read_tokens()
    pp(tokens)
    rules = read_rules()
    pp(rules)