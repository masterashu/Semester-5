import csv
from os import stat

def gen():
    final_state = '1'
    out = open('automaton.dot', 'w')
    out.write('digraph G {')
    done = set()
    reader = csv.reader(open('data.csv'))

    for i, row in enumerate(reader):
        if i == 0:
            continue
        goto, kernal, state, closure = row
        label = f'{state} \\n {kernal}'
        if state not in done:
            done.add(state)
            out.write(f'{state} [shape="box" label="{label}"];\n')

        if goto == 'Start':
            continue
        start, symbol = goto.lstrip('goto(').rstrip(')').split(', ')
        out.write(f'    {start} -> {state} [label="{symbol}"];\n')
    out.write(f' 99 [shape="bpx" label="Accept"];\n')
    out.write(f' 1 -> 9 [label="$"];\n')
    out.write('}')
    out.close()
