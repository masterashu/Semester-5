#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

namespace left_factoring {

class Production {
   public:
    char symbol{};
    string rule{};
    Production() {}

    Production(char a, string b) : symbol{a}, rule{b} {}
};

char Get_Unused_Symbol(vector<Production> Grammar) {
    for (char sym = 'A'; sym <= 'Z'; sym++) {
        bool found = false;
        for (int i = 0; i < Grammar.size(); i++) {
            if (Grammar[i].symbol == sym) {
                found = true;
                break;
            }
        }
        if (!found) {
            return sym;
        }
    }
    exit(-1);
}

void Do_Left_Factoring(vector<Production>& Grammar) {
    string terminal, nonterm, extra;
    string epsilon = "#";
    int a = -1, b = 0, c, f, q, n = Grammar.size(), m = 0;
    for (int cnt1 = 0; cnt1 < n; cnt1++) {
        bool flag = false;
        struct Production prodn_new[20];
        for (int cnt2 = cnt1 + 1;
             Grammar[cnt1].symbol == Grammar[cnt2].symbol &&
             Grammar[cnt1].rule.length() > 1 &&
             Grammar[cnt2].rule.length() > 1;) {
            char alpha = Grammar[cnt1].symbol;
            if (Grammar[cnt1].symbol == Grammar[cnt2].symbol) {
                int cnt = 0;
                int p = 0;
                alpha = Get_Unused_Symbol(Grammar);
                while ((Grammar[cnt1].rule[cnt] != '\0') &&
                       (Grammar[cnt2].rule[cnt] != '\0')) {
                    if (Grammar[cnt1].rule[cnt] == Grammar[cnt2].rule[cnt]) {
                        flag = true;
                        extra += Grammar[cnt2].rule[cnt];
                        p++;
                    } else {
                        if (p == 0) {
                            break;
                        } else {
                            prodn_new[++a].symbol = Grammar[cnt1].symbol;
                            prodn_new[a].rule = extra;
                            prodn_new[a].rule += alpha;
                            prodn_new[++a].symbol = alpha;
                            for (int g = cnt; g < Grammar[cnt2].rule.length();
                                 g++)
                                prodn_new[a].rule += Grammar[cnt2].rule[g];
                            prodn_new[++a].symbol = alpha;
                            for (int g = cnt; g < Grammar[cnt1].rule.length();
                                 g++)
                                prodn_new[a].rule += Grammar[cnt1].rule[g];
                            m = 1;
                            break;
                            n--;
                        }
                    }
                    cnt++;
                }
                if (Grammar[cnt1].rule[cnt] == '\0' && m == 0) {
                    prodn_new[++a].symbol = Grammar[cnt1].symbol;
                    prodn_new[a].rule = extra;
                    prodn_new[a].rule += alpha;
                    prodn_new[++a].symbol = alpha;
                    prodn_new[a].rule = epsilon;
                    prodn_new[++a].symbol = alpha;
                    for (int g = cnt; g < Grammar[cnt2].rule.length(); g++)
                        prodn_new[a].rule += Grammar[cnt2].rule[g];
                }
                if ((Grammar[cnt2].rule[cnt] == '\0') && (m == 0)) {
                    prodn_new[++a].symbol = Grammar[cnt1].symbol;
                    prodn_new[a].rule = extra;
                    prodn_new[a].rule += alpha;
                    prodn_new[++a].symbol = alpha;
                    prodn_new[a].rule = epsilon;
                    prodn_new[++a].symbol = alpha;
                    for (int g = cnt; g < Grammar[cnt1].rule.length(); g++)
                        prodn_new[a].rule += Grammar[cnt1].rule[g];
                }
                b++;
                m = 0;
                Grammar.erase(Grammar.begin() + cnt2);
                Grammar.push_back(prodn_new[a]);
                Grammar.push_back(prodn_new[a - 1]);
            }
        }
        if (flag) {
            Grammar.erase(Grammar.begin() + cnt1);
            Grammar.push_back(prodn_new[0]);
        }
    }

    int end;
    for (int cnt1 = 0; cnt1 < Grammar.size(); cnt1++) {
        for (int cnt2 = cnt1 + 1; cnt2 < Grammar.size(); cnt2++) {
            if (Grammar[cnt1].symbol == Grammar[cnt2].symbol &&
                Grammar[cnt1].rule == Grammar[cnt2].rule) {
                Grammar.erase(Grammar.begin() + cnt2);
            }
        }
        if (Grammar[cnt1].rule == "#") {
            Grammar[cnt1].rule = "epsilon";
        }
        end = cnt1;
    }
    struct Production temp = Grammar[end];
    Grammar[end] = Grammar[0];
    Grammar[0] = temp;
}

void Ready() {}

void AddProduction(string production, int length, vector<Production>& Grammar) {
    char sym = production[0];
    int i = 1;
    while (production[i] == ' ')
        i++;
    i += 2;
    while (production[i] == ' ')
        i++;
    string rule = "";
    for (int k = i; k < length; k++) {
        rule += production[k];
    }
    cout << sym << "->" << rule << endl;
    Grammar.push_back(Production(sym, rule));
}
}  // namespace left_factoring
