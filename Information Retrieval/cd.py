class Stack:
    def __init__(self):
        self.data=[]
        self.top=0
    
    def is_not_empty(self):
        return self.top
    
    def push(self,val):
        self.data.append(val)
        self.top=self.top+1
        
    def pop(self):
        self.top=self.top-1
        
    def get_top(self):
        return self.data[self.top-1]
    
    
class Production:
    
    def __init__(self,lhs,rhs):
        self.lhs=lhs
        self.rhs=list(rhs)
    

productions=[]
row=10
productions = [0]*row

def create_productions(productions):
    productions.append(Production('L',"En"))
    productions.append(Production('E',"E+T"))
    productions.append(Production('E',"T"))
    productions.append(Production('T',"T*F"))
    productions.append(Production('T',"F"))
    productions.append(Production('F',"F^G"))
    productions.append(Production('F',"G"))
    productions.append(Production('G',"-G"))
    productions.append(Production('G',"(E)"))
    productions.append(Production('G',"t"))
    
    return productions

def power(a,b):
    return int(a**b)

def semantic_actions(id,values):
    if id==1:
        t1=values.get_top()
        values.pop()
        t2=values.get_top()
        values.pop()
        t1=t1+t2
        values.push(t1)
        
    if(id == 3):
        t1 = values.get_top()
        values.pop()
        t2 = values.get_top()
        values.pop()
        t1 =int(t1)* int(t2)
        values.push(t1)
	
    if(id == 5):
        t1 = values.get_top()
        values.pop()
        t2 = values.get_top()
        values.pop()
        t2 = power(t2,t1)
        values.push(t2)
	
    if(id == 7):
        t1 = values.get_top()
        values.pop()
        t1 = -t1
        values.push(t1)
  

class goto_action:
    def __init__(self,flag,num,isAssigned):
        self.flag=flag
        self.num=num
        self.isAssigned=isAssigned

parsing_table=[[]]

row,col=(35,256)
parsing_table = [[0]*col]*row


def get_production_table(parsing_table):
    parsing_table[0][ord('E')] = goto_action(0,1,1)
    parsing_table[0][ord('T')] = goto_action(0,2,1)
    parsing_table[0][ord('F')] = goto_action(0,3,1)
    parsing_table[0][ord('G')] = goto_action(0,4,1)
    parsing_table[0][ord('t')] = goto_action(0,7,1)
    parsing_table[0][ord('(')] = goto_action(0,6,1)
    parsing_table[0][ord('-')] = goto_action(0,5,1)
    parsing_table[1][ord('n')] = goto_action(0,8,1)
    parsing_table[1][ord('+')] = goto_action(0,9,1)
    parsing_table[2][ord('n')] = goto_action(1,2,1)
    parsing_table[2][ord('+')] = goto_action(1,2,1)
    parsing_table[2][ord('*')] = goto_action(0,10,1)
    parsing_table[3][ord('n')] = goto_action(1,4,1)
    parsing_table[3][ord('+')] = goto_action(1,4,1)
    parsing_table[3][ord('*')] = goto_action(1,4,1)
    parsing_table[3][ord('^')] = goto_action(0,11,1)
    parsing_table[4][ord('+')] = goto_action(1,6,1)
    parsing_table[4][ord('*')] = goto_action(1,6,1)
    parsing_table[4][ord('^')] = goto_action(1,6,1)
    parsing_table[4][ord('n')] = goto_action(1,6,1)
    parsing_table[5][ord('-')] = goto_action(0,5,1)
    parsing_table[5][ord('(')] = goto_action(0,6,1)
    parsing_table[5][ord('t')] = goto_action(0,7,1)
    parsing_table[5][ord('G')] = goto_action(0,12,1)
    parsing_table[6][ord('-')] = goto_action(0,17,1)
    parsing_table[6][ord('(')] = goto_action(0,18,1)
    parsing_table[6][ord('t')] = goto_action(0,19,1)
    parsing_table[6][ord('E')] = goto_action(0,13,1)
    parsing_table[6][ord('T')] = goto_action(0,14,1)
    parsing_table[6][ord('F')] = goto_action(0,15,1)
    parsing_table[6][ord('G')] = goto_action(0,16,1)
    parsing_table[7][ord('+')] = goto_action(1,9,1)
    parsing_table[7][ord('*')] = goto_action(1,9,1)
    parsing_table[7][ord('^')] = goto_action(1,9,1)
    parsing_table[7][ord('n')] = goto_action(1,9,1)
    parsing_table[8][ord('$')] = goto_action(0,100,1)
    parsing_table[9][ord('-')] = goto_action(0,5,1)
    parsing_table[9][ord('(')] = goto_action(0,6,1)
    parsing_table[9][ord('t')] = goto_action(0,7,1)
    parsing_table[9][ord('T')] = goto_action(0,20,1)
    parsing_table[9][ord('F')] = goto_action(0,3,1)
    parsing_table[9][ord('G')] = goto_action(0,4,1)
    parsing_table[10][ord('-')] = goto_action(0,5,1)
    parsing_table[10][ord('(')] = goto_action(0,6,1)
    parsing_table[10][ord('t')] = goto_action(0,7,1)
    parsing_table[10][ord('F')] = goto_action(0,21,1)
    parsing_table[10][ord('G')] = goto_action(0,4,1)
    parsing_table[11][ord('-')] = goto_action(0,5,1)
    parsing_table[11][ord('(')] = goto_action(0,6,1)
    parsing_table[11][ord('t')] = goto_action(0,7,1)
    parsing_table[11][ord('G')] = goto_action(0,22,1)
    parsing_table[12][ord('+')] = goto_action(1,7,1)
    parsing_table[12][ord('*')] = goto_action(1,7,1)
    parsing_table[12][ord('^')] = goto_action(1,7,1)
    parsing_table[12][ord('n')] = goto_action(1,7,1)
    parsing_table[13][ord('+')] = goto_action(0,24,1)
    parsing_table[13][ord(')')] = goto_action(0,23,1)
    parsing_table[14][ord(')')] = goto_action(1,2,1)
    parsing_table[14][ord('+')] = goto_action(1,2,1)
    parsing_table[14][ord('*')] = goto_action(0,25,1)
    parsing_table[15][ord('^')] = goto_action(0,26,1)
    parsing_table[15][ord('+')] = goto_action(1,4,1)
    parsing_table[15][ord(')')] = goto_action(1,4,1)
    parsing_table[15][ord('*')] = goto_action(1,4,1)
    parsing_table[16][ord('^')] = goto_action(1,6,1)
    parsing_table[16][ord('+')] = goto_action(1,6,1)
    parsing_table[16][ord(')')] = goto_action(1,6,1)
    parsing_table[16][ord('*')] = goto_action(1,6,1)
    parsing_table[17][ord('-')] = goto_action(0,17,1)
    parsing_table[17][ord('(')] = goto_action(0,18,1)
    parsing_table[17][ord('t')] = goto_action(0,19,1)
    parsing_table[17][ord('G')] = goto_action(0,27,1)
    parsing_table[18][ord('-')] = goto_action(0,17,1)
    parsing_table[18][ord('(')] = goto_action(0,18,1)
    parsing_table[18][ord('t')] = goto_action(0,19,1)
    parsing_table[18][ord('E')] = goto_action(0,28,1)
    parsing_table[18][ord('T')] = goto_action(0,14,1)
    parsing_table[18][ord('F')] = goto_action(0,15,1)
    parsing_table[18][ord('G')] = goto_action(0,16,1)
    parsing_table[19][ord(')')] = goto_action(1,9,1)
    parsing_table[19][ord('+')] = goto_action(1,9,1)
    parsing_table[19][ord('*')] = goto_action(1,9,1)
    parsing_table[19][ord('^')] = goto_action(1,9,1)
    parsing_table[20][ord('n')] = goto_action(1,1,1)
    parsing_table[20][ord('+')] = goto_action(1,1,1)
    parsing_table[20][ord('*')] = goto_action(0,10,1)
    parsing_table[21][ord('n')] = goto_action(1,3,1)
    parsing_table[21][ord('+')] = goto_action(1,3,1)
    parsing_table[21][ord('*')] = goto_action(1,3,1)
    parsing_table[21][ord('^')] = goto_action(0,11,1)
    parsing_table[22][ord('n')] = goto_action(1,5,1)
    parsing_table[22][ord('+')] = goto_action(1,5,1)
    parsing_table[22][ord('*')] = goto_action(1,5,1)
    parsing_table[22][ord('^')] = goto_action(1,5,1)
    parsing_table[23][ord('n')] = goto_action(1,8,1)
    parsing_table[23][ord('+')] = goto_action(1,8,1)
    parsing_table[23][ord('*')] = goto_action(1,8,1)
    parsing_table[23][ord('^')] = goto_action(1,8,1)
    parsing_table[24][ord('-')] = goto_action(0,17,1)
    parsing_table[24][ord('(')] = goto_action(0,18,1)
    parsing_table[24][ord('t')] = goto_action(0,19,1)
    parsing_table[24][ord('T')] = goto_action(0,29,1)
    parsing_table[24][ord('F')] = goto_action(0,15,1)
    parsing_table[24][ord('G')] = goto_action(0,16,1)
    parsing_table[25][ord('-')] = goto_action(0,17,1)
    parsing_table[25][ord('(')] = goto_action(0,18,1)
    parsing_table[25][ord('t')] = goto_action(0,19,1)
    parsing_table[25][ord('F')] = goto_action(0,30,1)
    parsing_table[25][ord('G')] = goto_action(0,16,1)
    parsing_table[26][ord('-')] = goto_action(0,17,1)
    parsing_table[26][ord('(')] = goto_action(0,18,1)
    parsing_table[26][ord('t')] = goto_action(0,19,1)
    parsing_table[26][ord('G')] = goto_action(0,31,1)
    parsing_table[27][ord(')')] = goto_action(1,7,1)
    parsing_table[27][ord('+')] = goto_action(1,7,1)
    parsing_table[27][ord('^')] = goto_action(1,7,1)
    parsing_table[27][ord('*')] = goto_action(1,7,1)
    parsing_table[28][ord(')')] = goto_action(0,32,1)
    parsing_table[28][ord('+')] = goto_action(0,24,1)
    parsing_table[29][ord(')')] = goto_action(1,1,1)
    parsing_table[29][ord('+')] = goto_action(1,1,1)
    parsing_table[29][ord('*')] = goto_action(0,25,1)
    parsing_table[30][ord(')')] = goto_action(1,3,1)
    parsing_table[30][ord('+')] = goto_action(1,3,1)
    parsing_table[30][ord('*')] = goto_action(1,3,1)
    parsing_table[30][ord('^')] = goto_action(0,26,1)
    parsing_table[31][ord(')')] = goto_action(1,5,1)
    parsing_table[31][ord('+')] = goto_action(1,5,1)
    parsing_table[31][ord('*')] = goto_action(1,5,1)
    parsing_table[31][ord('^')] = goto_action(1,5,1)
    parsing_table[32][ord(')')] = goto_action(1,8,1)
    parsing_table[32][ord('+')] = goto_action(1,8,1)
    parsing_table[32][ord('^')] = goto_action(1,8,1)
    parsing_table[32][ord('*')] = goto_action(1,8,1)
    
    return parsing_table

def parse(string):
    inp,parsed,states,values=Stack(),Stack(),Stack(),Stack()
    inp.top=parsed.top=states.top=values.top=0
    parsed.push('$')
    inp.push('$')
    
    for i in range(len(string)-1,0,-1):
        inp.push(string[i])
    states.push(0)
    
    while inp.is_not_empty():
        print("$")
        for i in range(0,states.top):
            print(states.data[i])
        print(" ")
        for i in range(parsed.top-1,0,-1):
            print(inp.data[i])
        print(" ")
        
        for i in range(inp.top-1,0,-1):
            print(inp.data[i])
        
        print("\n")
        
        if (inp.get_top()>='0' and inp.get_top()<='9'):
            val=0
            while (inp.get_top()) >= '0' and (inp.get_top()) <= '9':
                val*=10
                val+=ord(inp.get_top())-48
                inp.pop()
            
            inp.push('t')
            values.push(val)
            
        if(parsing_table[states.get_top()][inp.get_top()].isAssigned==1):
            print("came here\n")
            return 0
        	

        if(parsing_table[states.get_top()][inp.get_top()].flag):
            semantic_actions(parsing_table[states.get_top()][inp.get_top()].num,values)
            pr = productions[parsing_table[states.get_top()][inp.get_top()].num]
            for i in range((pr.rhs).length(),0):
            	states.pop()
            	parsed.pop()
    
            if  (not parsing_table[states.get_top()][pr.LHS].isAssigned):
                print("came here2\n")
                return 0
    
            states.push(parsing_table[states.get_top()][pr.LHS].num)
            parsed.push(pr.LHS)
            
        else:
            states.push(parsing_table[states.get_top()][inp.get_top()].num)
            parsed.push(inp.get_top())


        if(states.get_top() == 100):
            states.pop()
            print(values.get_top())
            return 1


def main():
    create_productions(productions)
    get_production_table(parsing_table)
    string=input("Enter Input")
    status=parse(string)
    if status:
        print("Parsing Succesfull\n")
    else:
        print("Parsing failed\n")

if __name__ == "__main__":
    main()
