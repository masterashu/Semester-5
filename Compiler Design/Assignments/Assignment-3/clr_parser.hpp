#include "clr_table.hpp"

#ifndef __CLR_PARSER_HPP__
#define __CLR_PARSER_HPP__

class CLRParser {
   private:
    bool show_actions;
    CLRTable table;
    stack<int> states;
    stack<PairID> symbols;
    queue<pair<int, string>> input_token;

   public:
    CLRParser(bool show_actions) : show_actions(show_actions) {
        this->table = CLRTable();
        this->states = stack<int>();
        this->states.push(0);
        this->symbols = stack<PairID>();
        this->symbols.push(make_pair(DOLLAR, 0.0l));
        this->input_token = queue<pair<int, string>>();
    }

    int pending_character() { return (this->input_token.size() > 0); }

    void add_token_to_queue(pair<int, string> token) {
        this->input_token.push(token);
    }

    pair<int, string> get_next_token(FlexLexer* lexer) {
        if (this->pending_character()) {
            pair<int, string> token = this->input_token.front();
            this->input_token.pop();
            return token;
        } else {
            int symbol = lexer->yylex();
            string match = lexer->YYText();
            return pair<int, string>(symbol, match);
        }
    }

    int curr_state() { return this->states.top(); }

    int top_symbol() { return this->symbols.top().first; }

    void reduce(int production) {
        int prod_length = this->table.get_prod_len(production);
        while (prod_length--) {
            this->states.pop();
        }

        PairID next_symbol = this->get_reduced_symbol(production);
        this->symbols.push(next_symbol);

        int state =
            this->table.get_state(this->curr_state(), next_symbol.first);
        if (this->show_actions)
            cout << "NEXT    " << state << endl;
        this->states.push(state);
    }

    vector<PairID> pop_symbols_stack(int count) {
        vector<PairID> symbols = vector<PairID>();
        while (count--) {
            symbols.push_back(this->symbols.top());
            this->symbols.pop();
        }
        return symbols;
    }

    PairID get_reduced_symbol(int production) {
        double new_symbol_value = 0.0l;
        vector<PairID> symbols;
        int prod_leng = this->table.get_prod_len(production);
        int prod_lhs = this->table.get_prod_lhs(production);

        switch (production) {
            case 1:  // E -> E + T {E.val = E1.val + T.val} 
                symbols = this->pop_symbols_stack(prod_leng);
                new_symbol_value = symbols[0].second + symbols[2].second;
                cout << "Reducing E -> E + T \t|\t" << new_symbol_value << " <- "
                     << symbols[2].second << " + " << symbols[0].second << endl;
                break;

            case 3:  // T -> T * F {T.val = T1.val * F.val}
                symbols = this->pop_symbols_stack(prod_leng);
                new_symbol_value = symbols[0].second * symbols[2].second;
                cout << "Reducing T -> T * F \t|\t" << new_symbol_value << " <- "
                     << symbols[2].second << " * " << symbols[0].second << endl;
                break;

            case 5:  // F -> F ^ G {F.val = F1.val ^ G.val}
                symbols = this->pop_symbols_stack(prod_leng);
                new_symbol_value = powf64(symbols[2].second, symbols[0].second);
                cout << "Reducing F -> F ^ G \t|\t" << new_symbol_value << " <- "
                     << symbols[2].second << " ^ " << symbols[0].second << endl;
                break;

            case 7:  // G -> - Z {G.val = -1 * Z.val}
                symbols = this->pop_symbols_stack(prod_leng);
                new_symbol_value = (symbols[0].second * (-1.0l));
                cout << "Reducing G -> - G \t|\t" << new_symbol_value << " <-  - "
                     << symbols[0].second << endl;
                break;

            case 9:  // Z -> ( E ) {Z.val = E.val}
                symbols = this->pop_symbols_stack(prod_leng);
                new_symbol_value = symbols[1].second;
                cout << "Reducing Z -> ( E ) \t|\t" << new_symbol_value << " <-  ( "
                     << symbols[1].second << " )" << endl;
                break;

            case 0:   // L -> E {L.val = E.val}
            case 2:   // E -> T {E.val = T.val}
            case 4:   // T -> F {T.val = F.val}
            case 6:   // F -> G {F.val = G.val}
            case 8:   // G -> Z {G.val = Z.val}
            case 10:  // Z -> num {Z.val = num.lex_val}
                symbols = this->pop_symbols_stack(prod_leng);
                new_symbol_value = symbols[0].second;
                break;

            default:
                break;
        }
        return PairID(prod_lhs, new_symbol_value);
    }

    void shift(int state, pair<int, string> token) {
        long lex_val = 0;
        if (token.first == NUM) {
            lex_val = stod(token.second);
        }
        this->states.push(state);
        this->symbols.push(make_pair(token.first, lex_val));
    }

    void accept() {
        cout << "Accepted!\n";
        cout << "Final Value: " << this->symbols.top().second << endl;
    }

    void run(FlexLexer* lexer) {
        while (true) {
            pair<int, string> token = this->get_next_token(lexer);
            // cout << "Token" << token.first << ':' << token.second << endl;
            int state = this->curr_state(), symbol = token.first;
            Pair action = this->table.get_action(state, symbol);

            if (action.first == SHIFT) {
                if (this->show_actions)
                    cout << "SHIFT\t" << action.second << endl;

                this->shift(action.second, token);
            } else if (action.first == REDUCE) {
                if (this->show_actions)
                    cout << "REDUCE\t" << action.second << endl;

                this->reduce(action.second);
                this->add_token_to_queue(token);
            } else if (action.first == STOP) {
                if (this->show_actions)
                    cout << "STOP\t";

                break;
            } else if (action.first == ACCEPT) {
                if (this->show_actions)
                    cout << "ACCEPT\t";

                this->accept();
                break;
            }
        }
    }
};

#endif