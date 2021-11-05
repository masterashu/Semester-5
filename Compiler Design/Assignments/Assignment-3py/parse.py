from csv import reader
from lex import lex, TOKENS, PRODUCTIONS
from enum import Enum
from pprint import pprint

class Action(Enum):
    Shift = 1
    Reduce = 2
    Stop = 3
    Accept = 4

def get_act(act: str):
    if not act:
        return (Action.Stop, None)
    elif act == 'acc':
        return (Action.Accept, None)
    elif act[0] == 'r':
        return (Action.Reduce, int(act.lstrip('r')))
    elif act[0] == 's':
        return (Action.Shift, int(act.lstrip('s')))

class Parser:
    def __init__(self):
        self.action = dict()
        self.goto = dict()
        # Load table
        with open('parse_table.csv') as f:
            csv = reader(f)
            symbols = dict()
            for row in csv:
                if row[0] == 'State':
                    for i, sym in enumerate(row[1:], start=1):
                        symbols[i] = sym
                else:
                    state = int(row[0])
                    for i, act in enumerate(row[1:], start=1):
                        sym = symbols[i]
                        if sym.isupper():
                            self.goto[(state, sym)] = int(act) if act else None
                        else:
                            self.action[(state, sym)] = get_act(act)

    def parser(self, data):
        self.queue = []
        self.states = [0]
        self.symbols = [('$', None)]
        for token in lex(data):
            if self.queue:
                self.queue.append(token)
                token = self.queue.pop(0)
            # Get Action
            state = self.states[-1]
            action = self.action[(state, token[0])]
            if action[0] == Action.Accept:
                print("Accept")
                print("Output:", self.symbols[-1][1])
                return
            elif action[0] == Action.Stop:
                print("Stop")
                return
            elif action[0] == Action.Shift:
                print("Shift", action[1])
                self.states.append(action[1])
                self.symbols.append(token)
                pass
            elif action[0] == Action.Reduce:
                print("Reduce", action[1])
                print('-------------------------------')
                print("Before Reduction")
                print(self.states)
                print(self.symbols)
                self.reduce_action(action)
                self.queue.insert(0, token)
                print("After Reduction")
                print(self.states)
                print(self.symbols)
                print('-------------------------------')
    
    def reduce_action(self, action):
        prod_len = len(PRODUCTIONS[action[1]]) - 3 # sub 'L->' part
        prod_lhs = PRODUCTIONS[action[1]][0]
        popped = []
        for i in range(prod_len):
            self.states.pop(-1)
            popped.insert(0, self.symbols.pop(-1))
        # Do SDT magic
        new_val = 0
        if prod_len == 1:
            new_val = popped[0][1]
        elif prod_len == 2:
            new_val = -popped[1][1]
        elif prod_len == 3:
            if popped[1][0] == '*':
                new_val = popped[0][1] * popped[2][1]
            if popped[1][0] == '+':
                new_val = popped[0][1] + popped[2][1]
            if popped[1][0] == '^':
                new_val = popped[0][1] ** popped[2][1]
            if popped[0][0] == '(':
                new_val = popped[1][1]
        # Magic done
        self.symbols.append((prod_lhs, new_val))
        print('Applying', PRODUCTIONS[action[1]])
        self.states.append(self.goto[(self.states[-1], prod_lhs)])

if __name__ == "__main__":
    p = Parser()
    p.parser(input())
