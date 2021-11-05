import csv

def gen():
    final_state = '1'
    out = open('lr1_automaton.dot', 'w')
    out.write('''
digraph G {
    nodesep = 0.05;                 // even node distribution
    rankdir=TB;
    splines=ortho;
    overlap=false;
    nodesep=0.4;
    node[width=0.5, height=0.5];
    edge[style=solid, weight=0, color=grey];
''')
    states = {}
    edges = []
    reader = csv.reader(open('data.csv'))
    for i, row in enumerate(reader):
        if i == 0:
            continue
        goto, kernal, state, closure = row
        kernal = kernal.replace('[', '').replace(']', '').replace('{', '').replace('}', '').replace(';', '|').replace('.', '&#8901;').replace('-', '\\-').replace('>', '\\>').replace('*', '\\*').replace('$', '\\$').replace('+', '\\+').replace('^', '\\^').replace('(', '\\(').replace(')', '\\)')
        label = f'{{ {state} | {kernal} }}'
        if state not in states:
            states[state] = label
        
        if goto == 'Start':
            continue
        start, symbol = goto.lstrip('goto(').rstrip(')').split(', ')
        edges.append((start, state, symbol))

    for k,v in states.items():
        out.write(f'    {k} [shape="record" label="{v}"];\n')

    for start, end, symbol in edges:
        out.write(f'    {start} -> {end} [label="{symbol}"];\n')

    out.write(f' 1999 [shape="record" label="{{Accept}}" color=green style=filled];\n')
    out.write(f' 1 -> 1999 [shape="record" label="$"];\n')

    out.write('}')
    out.close()

if __name__ == "__main__":
    gen()
        

