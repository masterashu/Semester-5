#include <bits/stdc++.h>

#ifndef __CLR_TABLE_HPP__
#define __CLR_TABLE_HPP__

using namespace std;

#define Pair pair<int, int>
#define PairID pair<int, double>

/* Productions
0.	L -> E
1. 	E -> E + T 
2.	E -> T
3.	T -> T * F 
4.	T -> F
5.	F -> F ^ G
6.	F -> G
7.	G -> - G
8.	G -> Z
9.	Z ->( E )
10.	Z -> n
*/

/*
|-----------------------------------CLR Parse Table----------------------------------|
| State |------------------ACTION-----------------------|-----------GOTO-------------|
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
|       | +   | *   | ^   | -   | (   | )   | n   | $   | L | E  | T  | F  | G  | Z  |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 0     |     |     |     | s5  | s7  |     | s8  |     |   | 1  | 2  | 3  | 4  | 6  |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 1     | s9  |     |     |     |     |     |     | acc |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 2     | r2  | s10 |     |     |     |     |     | r2  |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 3     | r4  | r4  | s11 |     |     |     |     | r4  |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 4     | r6  | r6  | r6  |     |     |     |     | r6  |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 5     |     |     |     | s5  | s7  |     | s8  |     |   |    |    |    | 12 | 6  |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 6     | r8  | r8  | r8  |     |     |     |     | r8  |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 7     |     |     |     | s17 | s19 |     | s20 |     |   | 13 | 14 | 15 | 16 | 18 |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 8     | r10 | r10 | r10 |     |     |     |     | r10 |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 9     |     |     |     | s5  | s7  |     | s8  |     |   |    | 21 | 3  | 4  | 6  |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 10    |     |     |     | s5  | s7  |     | s8  |     |   |    |    | 22 | 4  | 6  |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 11    |     |     |     | s5  | s7  |     | s8  |     |   |    |    |    | 23 | 6  |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 12    | r7  | r7  | r7  |     |     |     |     | r7  |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 13    | s25 |     |     |     |     | s24 |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 14    | r2  | s26 |     |     |     | r2  |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 15    | r4  | r4  | s27 |     |     | r4  |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 16    | r6  | r6  | r6  |     |     | r6  |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 17    |     |     |     | s17 | s19 |     | s20 |     |   |    |    |    | 28 | 18 |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 18    | r8  | r8  | r8  |     |     | r8  |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 19    |     |     |     | s17 | s19 |     | s20 |     |   | 29 | 14 | 15 | 16 | 18 |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 20    | r10 | r10 | r10 |     |     | r10 |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 21    | r1  | s10 |     |     |     |     |     | r1  |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 22    | r3  | r3  | s11 |     |     |     |     | r3  |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 23    | r5  | r5  | r5  |     |     |     |     | r5  |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 24    | r9  | r9  | r9  |     |     |     |     | r9  |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 25    |     |     |     | s17 | s19 |     | s20 |     |   |    | 30 | 15 | 16 | 18 |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 26    |     |     |     | s17 | s19 |     | s20 |     |   |    |    | 31 | 16 | 18 |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 27    |     |     |     | s17 | s19 |     | s20 |     |   |    |    |    | 32 | 18 |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 28    | r7  | r7  | r7  |     |     | r7  |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 29    | s25 |     |     |     |     | s33 |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 30    | r1  | s26 |     |     |     | r1  |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 31    | r3  | r3  | s27 |     |     | r3  |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 32    | r5  | r5  | r5  |     |     | r5  |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
| 33    | r9  | r9  | r9  |     |     | r9  |     |     |   |    |    |    |    |    |
|-------|-----|-----|-----|-----|-----|-----|-----|-----|---|----|----|----|----|----|
*/

// NonTerminal SYMBOLS
#define L 11
#define E 12
#define T 13
#define F 14
#define G 15
#define Z 16

// Terminal SYMBOLS
#define ADD 1
#define MUL 2
#define POW 3
#define MINUS 4
#define PARASTART 5
#define PARAEND 6
#define NUM 7
#define DOLLAR 0

// Actions
#define SHIFT 0
#define REDUCE 1
#define ACCEPT 2
#define STOP 3

class CLRTable {
   private:
    int no_of_states = 34;
    // < STATE, SYMBOL > := <ACTION, NUMBER>
    map<Pair, 		Pair > action_table;

    // < STATE, NonTerminal > := STATE
    map<Pair, int> goto_table;

    map<int, string> actionMap = {{SHIFT, "S"}, {REDUCE, "R"}, {ACCEPT, "ACCEPT"}, {STOP, ""}};
    
    map<int, string> symbolTable = { {ADD, "+"}, {MUL, "*"}, {POW, "^"}, {MINUS, "-"}, {PARASTART, "("}, {PARAEND, ")"}, {NUM, "num"}, {DOLLAR, "$"}, {L, "L"}, {T, "T"}, {E, "E"}, {F, "F"}, {G, "G"}, {Z, "Z"} };

	map<int, int> ProductionLHS = {{0, L}, {1, E}, {2, E}, {3, T}, {4, T}, {5, F}, {6, F}, {7, G}, {8, G}, {9, Z}, {10, Z}};

	map<int, int> ProductionRHSLength = {{0, 1}, {1, 3}, {2, 1}, {3, 3}, {4, 1}, {5, 3}, {6, 1}, {7, 2}, {8, 1}, {9, 3}, {10, 1}};

   public:
    CLRTable() {
        this->action_table = map<Pair, Pair >();
        this->goto_table = map<Pair, int >();
		this->populate_table();
    }

	int get_prod_lhs(int prod){
		return this->ProductionLHS[prod];
	}

	int get_prod_len(int prod){
		return this->ProductionRHSLength[prod];
	}

    void populate_table();

    Pair get_action(int state, int symbol) {
		if (this->action_table.find(Pair(state, symbol)) == this->action_table.end()){
			return Pair(STOP, 0);
		}
        return this->action_table[Pair(state, symbol)];
    }

    int get_state(int state, int non_terminal) {
		if (this->goto_table.find(Pair(state, non_terminal)) == this->goto_table.end()){
			return -1;
		}
        return this->goto_table[Pair(state, non_terminal)];
    }
};

void CLRTable::populate_table() {
    this->action_table.insert(make_pair(Pair(0, MINUS),			Pair(SHIFT, 5)));
    this->action_table.insert(make_pair(Pair(0, PARASTART), 	Pair(SHIFT, 7)));
    this->action_table.insert(make_pair(Pair(0, NUM),			Pair(SHIFT, 8)));

    this->action_table.insert(make_pair(Pair(1, ADD),			Pair(SHIFT, 9)));
    this->action_table.insert(make_pair(Pair(1, DOLLAR),		Pair(ACCEPT, 0)));

    this->action_table.insert(make_pair(Pair(2, ADD),			Pair(REDUCE, 2)));
    this->action_table.insert(make_pair(Pair(2, MUL),			Pair(SHIFT, 10)));
    this->action_table.insert(make_pair(Pair(2, DOLLAR),		Pair(REDUCE, 2)));

    this->action_table.insert(make_pair(Pair(3, ADD),			Pair(REDUCE, 4)));
    this->action_table.insert(make_pair(Pair(3, MUL),			Pair(REDUCE, 4)));
    this->action_table.insert(make_pair(Pair(3, POW),			Pair(SHIFT, 11)));
    this->action_table.insert(make_pair(Pair(3, DOLLAR),    	Pair(REDUCE, 4)));

    this->action_table.insert(make_pair(Pair(4, ADD),			Pair(REDUCE, 6)));
    this->action_table.insert(make_pair(Pair(4, MUL),			Pair(REDUCE, 6)));
    this->action_table.insert(make_pair(Pair(4, POW),			Pair(REDUCE, 6)));
    this->action_table.insert(make_pair(Pair(4, DOLLAR),    	Pair(REDUCE, 6)));
    
	this->action_table.insert(make_pair(Pair(5, MINUS), 	    Pair(SHIFT, 5)));
	this->action_table.insert(make_pair(Pair(5, PARASTART),	    Pair(SHIFT, 7)));
    this->action_table.insert(make_pair(Pair(5, NUM),			Pair(SHIFT, 8)));

	this->action_table.insert(make_pair(Pair(6, ADD),			Pair(REDUCE, 8)));
    this->action_table.insert(make_pair(Pair(6, MUL),			Pair(REDUCE, 8)));
    this->action_table.insert(make_pair(Pair(6, POW),			Pair(REDUCE, 8)));
    this->action_table.insert(make_pair(Pair(6, DOLLAR),    	Pair(REDUCE, 8)));
    
	this->action_table.insert(make_pair(Pair(7, MINUS),		    Pair(SHIFT, 17)));
	this->action_table.insert(make_pair(Pair(7, PARASTART),	    Pair(SHIFT, 19)));
	this->action_table.insert(make_pair(Pair(7, NUM),			Pair(SHIFT, 20)));
    
	this->action_table.insert(make_pair(Pair(8, ADD),			Pair(REDUCE, 10)));
    this->action_table.insert(make_pair(Pair(8, MUL),			Pair(REDUCE, 10)));
    this->action_table.insert(make_pair(Pair(8, POW),			Pair(REDUCE, 10)));
    this->action_table.insert(make_pair(Pair(8, DOLLAR),    	Pair(REDUCE, 10)));
    
	this->action_table.insert(make_pair(Pair(9, MINUS),		    Pair(SHIFT, 5)));
	this->action_table.insert(make_pair(Pair(9, PARASTART),	    Pair(SHIFT, 7)));
	this->action_table.insert(make_pair(Pair(9, NUM),			Pair(SHIFT, 8)));
    
	this->action_table.insert(make_pair(Pair(10, MINUS),		Pair(SHIFT, 5)));
	this->action_table.insert(make_pair(Pair(10, PARASTART),	Pair(SHIFT, 7)));
	this->action_table.insert(make_pair(Pair(10, NUM),		    Pair(SHIFT, 8)));
    
	this->action_table.insert(make_pair(Pair(11, MINUS),		Pair(SHIFT, 5)));
	this->action_table.insert(make_pair(Pair(11, PARASTART),	Pair(SHIFT, 7)));
	this->action_table.insert(make_pair(Pair(11, NUM),		    Pair(SHIFT, 8)));
    
	this->action_table.insert(make_pair(Pair(12, ADD),		    Pair(REDUCE, 7)));
    this->action_table.insert(make_pair(Pair(12, MUL),		    Pair(REDUCE, 7)));
    this->action_table.insert(make_pair(Pair(12, POW),		    Pair(REDUCE, 7)));
    this->action_table.insert(make_pair(Pair(12, DOLLAR),    	Pair(REDUCE, 7)));
    
    this->action_table.insert(make_pair(Pair(13, ADD),		    Pair(SHIFT, 25)));
    this->action_table.insert(make_pair(Pair(13, PARAEND),	    Pair(SHIFT, 24)));

    this->action_table.insert(make_pair(Pair(14, ADD),	    	Pair(REDUCE, 2)));
    this->action_table.insert(make_pair(Pair(14, MUL),		    Pair(SHIFT, 26)));
    this->action_table.insert(make_pair(Pair(14, PARAEND),	    Pair(REDUCE, 2)));
	
    this->action_table.insert(make_pair(Pair(15, ADD),	    	Pair(REDUCE, 4)));
    this->action_table.insert(make_pair(Pair(15, MUL),	    	Pair(REDUCE, 4)));
	this->action_table.insert(make_pair(Pair(15, POW),	    	Pair(SHIFT, 27)));
    this->action_table.insert(make_pair(Pair(15, PARAEND),  	Pair(REDUCE, 4)));

	this->action_table.insert(make_pair(Pair(16, ADD),		    Pair(REDUCE, 6)));
    this->action_table.insert(make_pair(Pair(16, MUL),		    Pair(REDUCE, 6)));
    this->action_table.insert(make_pair(Pair(16, POW),		    Pair(REDUCE, 6)));
    this->action_table.insert(make_pair(Pair(16, PARAEND),      Pair(REDUCE, 6)));

    this->action_table.insert(make_pair(Pair(17, MINUS),        Pair(SHIFT, 17)));
    this->action_table.insert(make_pair(Pair(17, PARASTART),    Pair(SHIFT, 19)));
    this->action_table.insert(make_pair(Pair(17, NUM), 		    Pair(SHIFT, 20)));

    this->action_table.insert(make_pair(Pair(18, ADD), 		    Pair(REDUCE, 8)));
    this->action_table.insert(make_pair(Pair(18, MUL), 		    Pair(REDUCE, 8)));
    this->action_table.insert(make_pair(Pair(18, POW), 		    Pair(REDUCE, 8)));
    this->action_table.insert(make_pair(Pair(18, PARAEND),  	Pair(REDUCE, 8)));

    this->action_table.insert(make_pair(Pair(19, MINUS), 		Pair(SHIFT, 17)));
    this->action_table.insert(make_pair(Pair(19, PARASTART), 	Pair(SHIFT, 19)));
    this->action_table.insert(make_pair(Pair(19, NUM), 		    Pair(SHIFT, 20)));

  	this->action_table.insert(make_pair(Pair(20, ADD), 		    Pair(REDUCE, 10)));
    this->action_table.insert(make_pair(Pair(20, MUL), 		    Pair(REDUCE, 10)));
    this->action_table.insert(make_pair(Pair(20, POW), 		    Pair(REDUCE, 10)));
    this->action_table.insert(make_pair(Pair(20, PARAEND), 	    Pair(REDUCE, 10)));

    this->action_table.insert(make_pair(Pair(21, ADD), 		    Pair(REDUCE, 1)));
    this->action_table.insert(make_pair(Pair(21, MUL), 		    Pair(SHIFT, 10)));
    this->action_table.insert(make_pair(Pair(21, DOLLAR), 	    Pair(REDUCE, 1)));

    this->action_table.insert(make_pair(Pair(22, ADD), 		    Pair(REDUCE, 3)));
    this->action_table.insert(make_pair(Pair(22, MUL), 		    Pair(REDUCE, 3)));
    this->action_table.insert(make_pair(Pair(22, POW), 		    Pair(SHIFT, 11)));
    this->action_table.insert(make_pair(Pair(22, DOLLAR), 	    Pair(REDUCE, 3)));

    this->action_table.insert(make_pair(Pair(23, ADD), 		    Pair(REDUCE, 5)));
    this->action_table.insert(make_pair(Pair(23, MUL), 		    Pair(REDUCE, 5)));
    this->action_table.insert(make_pair(Pair(23, POW), 		    Pair(REDUCE, 5)));
    this->action_table.insert(make_pair(Pair(23, DOLLAR), 	    Pair(REDUCE, 5)));

    this->action_table.insert(make_pair(Pair(24, ADD), 		    Pair(REDUCE, 9)));
    this->action_table.insert(make_pair(Pair(24, MUL), 		    Pair(REDUCE, 9)));
    this->action_table.insert(make_pair(Pair(24, POW), 		    Pair(REDUCE, 9)));
    this->action_table.insert(make_pair(Pair(24, DOLLAR), 	    Pair(REDUCE, 9)));

    this->action_table.insert(make_pair(Pair(25, MINUS), 		Pair(SHIFT, 17)));
    this->action_table.insert(make_pair(Pair(25, PARASTART), 	Pair(SHIFT, 19)));
    this->action_table.insert(make_pair(Pair(25, NUM), 		    Pair(SHIFT, 20)));

    this->action_table.insert(make_pair(Pair(26, MINUS), 		Pair(SHIFT, 17)));
    this->action_table.insert(make_pair(Pair(26, PARASTART), 	Pair(SHIFT, 19)));
    this->action_table.insert(make_pair(Pair(26, NUM), 		    Pair(SHIFT, 20)));

    this->action_table.insert(make_pair(Pair(27, MINUS), 		Pair(SHIFT, 17)));
    this->action_table.insert(make_pair(Pair(27, PARASTART), 	Pair(SHIFT, 19)));
    this->action_table.insert(make_pair(Pair(27, NUM), 		    Pair(SHIFT, 20)));

    this->action_table.insert(make_pair(Pair(28, ADD), 		    Pair(REDUCE, 7)));
    this->action_table.insert(make_pair(Pair(28, MUL), 		    Pair(REDUCE, 7)));
    this->action_table.insert(make_pair(Pair(28, POW), 		    Pair(REDUCE, 7)));
    this->action_table.insert(make_pair(Pair(28, PARAEND), 	    Pair(REDUCE, 7)));

	this->action_table.insert(make_pair(Pair(29, ADD), 		    Pair(SHIFT, 25)));
    this->action_table.insert(make_pair(Pair(29, PARAEND),  	Pair(SHIFT, 33)));

	this->action_table.insert(make_pair(Pair(30, ADD), 		    Pair(REDUCE, 1)));
    this->action_table.insert(make_pair(Pair(30, MUL), 		    Pair(SHIFT, 26)));
    this->action_table.insert(make_pair(Pair(30, PARAEND), 	    Pair(REDUCE, 1)));

    this->action_table.insert(make_pair(Pair(31, ADD), 		    Pair(REDUCE, 3)));
    this->action_table.insert(make_pair(Pair(31, MUL), 		    Pair(REDUCE, 3)));
    this->action_table.insert(make_pair(Pair(31, POW), 		    Pair(SHIFT, 27)));
    this->action_table.insert(make_pair(Pair(31, PARAEND),  	Pair(REDUCE, 3)));

    this->action_table.insert(make_pair(Pair(32, ADD), 		    Pair(REDUCE, 5)));
    this->action_table.insert(make_pair(Pair(32, MUL), 	    	Pair(REDUCE, 5)));
    this->action_table.insert(make_pair(Pair(32, POW), 		    Pair(REDUCE, 5)));
    this->action_table.insert(make_pair(Pair(32, PARAEND),  	Pair(REDUCE, 5)));

    this->action_table.insert(make_pair(Pair(33, ADD), 	    	Pair(REDUCE, 9)));
    this->action_table.insert(make_pair(Pair(33, MUL), 		    Pair(REDUCE, 9)));
    this->action_table.insert(make_pair(Pair(33, POW), 		    Pair(REDUCE, 9)));
    this->action_table.insert(make_pair(Pair(33, PARAEND),  	Pair(REDUCE, 9)));

	this->goto_table.insert(make_pair(Pair(0, E), 1));
	this->goto_table.insert(make_pair(Pair(0, T), 2));
	this->goto_table.insert(make_pair(Pair(0, F), 3));
	this->goto_table.insert(make_pair(Pair(0, G), 4));
	this->goto_table.insert(make_pair(Pair(0, Z), 6));

	this->goto_table.insert(make_pair(Pair(5, G), 12));
	this->goto_table.insert(make_pair(Pair(5, Z), 6));

	this->goto_table.insert(make_pair(Pair(7, E), 13));
	this->goto_table.insert(make_pair(Pair(7, T), 14));
	this->goto_table.insert(make_pair(Pair(7, F), 15));
	this->goto_table.insert(make_pair(Pair(7, G), 16));
	this->goto_table.insert(make_pair(Pair(7, Z), 18));

	this->goto_table.insert(make_pair(Pair(9, T), 21));
	this->goto_table.insert(make_pair(Pair(9, F), 3));
	this->goto_table.insert(make_pair(Pair(9, G), 4));
	this->goto_table.insert(make_pair(Pair(9, Z), 6));

	this->goto_table.insert(make_pair(Pair(10, F), 22));
	this->goto_table.insert(make_pair(Pair(10, G), 4));
	this->goto_table.insert(make_pair(Pair(10, Z), 6));
	
	this->goto_table.insert(make_pair(Pair(11, G), 23));
	this->goto_table.insert(make_pair(Pair(11, Z), 6));
	
	this->goto_table.insert(make_pair(Pair(17, G), 28));
	this->goto_table.insert(make_pair(Pair(17, Z), 18));

	this->goto_table.insert(make_pair(Pair(19, E), 29));
	this->goto_table.insert(make_pair(Pair(19, T), 14));
	this->goto_table.insert(make_pair(Pair(19, F), 15));
	this->goto_table.insert(make_pair(Pair(19, G), 16));
	this->goto_table.insert(make_pair(Pair(19, Z), 18));

	this->goto_table.insert(make_pair(Pair(25, T), 30));
    this->goto_table.insert(make_pair(Pair(25, F), 15));
    this->goto_table.insert(make_pair(Pair(25, G), 16));
    this->goto_table.insert(make_pair(Pair(25, Z), 18));

    this->goto_table.insert(make_pair(Pair(26, F), 31));
    this->goto_table.insert(make_pair(Pair(26, G), 16));
    this->goto_table.insert(make_pair(Pair(26, Z), 18));

    this->goto_table.insert(make_pair(Pair(27, G), 32));
    this->goto_table.insert(make_pair(Pair(27, Z), 18));
};

#endif
