#include <algorithm>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Production {

  public:
    string head{};
    string body{};
    Production() {
    }

    Production(string h, string b)
        : head{h}, body{b} {
    }
};

vector<Production> Grammar_Input() {
    cout << "Enter the number of productions:";
    int n;
    cin >> n;

    cout << "\nEnter epsilon as epsilon" << endl;
    vector<Production> Grammar;

    for (int i = 1; i <= n; i++) {
        string head{};
        string body{};
        cout << endl
             << " production number - " << i << endl;
        cout << "enter the head : ";
        cin >> head;
        cout << "enter the body : ";
        cin >> body;
        Grammar.push_back(Production{head, body});
    }

    return Grammar;
}

void Remove_Unit_Productions(vector<Production> &Grammar) { //Leave this...
}

void Remove_Epsilon_Productions(vector<Production> &Grammar) // leave this...
{
}

void Do_Left_Factoring(vector<Production> &Grammar) {
    string terminal, nonterm, extra;
    string epsilon = "^";
    int a = -1, b = 0, c, f, q, n = Grammar.size(), m = 0;
    for (int cnt1 = 0; cnt1 < n; cnt1++) {
        bool flag = false;
        struct Production prodn_new[20];
        for (int cnt2 = cnt1 + 1; Grammar[cnt1].head == Grammar[cnt2].head && Grammar[cnt1].body.length() > 1 && Grammar[cnt2].body.length() > 1;) {
            string alpha = Grammar[cnt1].head;
            if (Grammar[cnt1].head == Grammar[cnt2].head) {
                int cnt = 0;
                int p = 0;
                alpha += "'";
                while ((Grammar[cnt1].body[cnt] != '\0') && (Grammar[cnt2].body[cnt] != '\0')) {
                    if (Grammar[cnt1].body[cnt] == Grammar[cnt2].body[cnt]) {
                        flag = true;
                        extra += Grammar[cnt2].body[cnt];
                        p++;
                    } else {
                        if (p == 0) {
                            break;
                        } else {
                            prodn_new[++a].head = Grammar[cnt1].head;
                            prodn_new[a].body = extra;
                            prodn_new[a].body += alpha;
                            prodn_new[++a].head = alpha;
                            for (int g = cnt; g < Grammar[cnt2].body.length(); g++)
                                prodn_new[a].body += Grammar[cnt2].body[g];
                            prodn_new[++a].head = alpha;
                            for (int g = cnt; g < Grammar[cnt1].body.length(); g++)
                                prodn_new[a].body += Grammar[cnt1].body[g];
                            m = 1;
                            break;
                            n--;
                        }
                    }
                    cnt++;
                }
                if (Grammar[cnt1].body[cnt] == '\0' && m == 0) {
                    prodn_new[++a].head = Grammar[cnt1].head;
                    prodn_new[a].body = extra;
                    prodn_new[a].body += alpha;
                    prodn_new[++a].head = alpha;
                    prodn_new[a].body = epsilon;
                    prodn_new[++a].head = alpha;
                    for (int g = cnt; g < Grammar[cnt2].body.length(); g++)
                        prodn_new[a].body += Grammar[cnt2].body[g];
                }
                if ((Grammar[cnt2].body[cnt] == '\0') && (m == 0)) {
                    prodn_new[++a].head = Grammar[cnt1].head;
                    prodn_new[a].body = extra;
                    prodn_new[a].body += alpha;
                    prodn_new[++a].head = alpha;
                    prodn_new[a].body = epsilon;
                    prodn_new[++a].head = alpha;
                    for (int g = cnt; g < Grammar[cnt1].body.length(); g++)
                        prodn_new[a].body += Grammar[cnt1].body[g];
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
            if (Grammar[cnt1].head == Grammar[cnt2].head && Grammar[cnt1].body == Grammar[cnt2].body) {
                Grammar.erase(Grammar.begin() + cnt2);
            }
        }
        if (Grammar[cnt1].body == "^") {
            Grammar[cnt1].body = "epsilon";
        }
        end = cnt1;
    }
    struct Production temp = Grammar[end];
    Grammar[end] = Grammar[0];
    Grammar[0] = temp;
}

int main() {
    vector<Production> Grammar = Grammar_Input();

    Remove_Unit_Productions(Grammar);
    Remove_Epsilon_Productions(Grammar);

    Do_Left_Factoring(Grammar);

    for (int i = 0; i < Grammar.size(); i++) {
        cout
            << Grammar[i].head << " --> " << Grammar[i].body << endl;
    }
}