TOKENS = {
    "*",
    "-",
    "+",
    "^",
    "(",
    ")",
    "num",
    "$",
    "L",
    "E",
    "T",
    "F",
    "G",
    "Z",
}

PRODUCTIONS = {
    0: "L->E",
    1: "E->E+T",
    2: "E->T",
    3: "T->T*F",
    4: "T->F",
    5: "F->F^G",
    6: "F->G",
    7: "G->-Z",
    8: "G->Z",
    9: "Z->(E)",
    10: "Z->n",
}


def lex(data):
    num = ""
    for i in data:
        if i in ("*", "-", "+", "^", "(", ")"):
            if num:
                yield ('num', int(num))
                num = ""
            yield (i, None)
        elif i.isdigit():
            num += i
        elif not i.isspace():
            # Break Invalid Character
            yield (-1, None)
    if num:
        yield ("num", int(num))
        num = ""
    while True:
        yield ('$', None)

if __name__ == "__main__":
    for i in lex('10+2'):
        print(i)
        if i[0] == '$':
            break
