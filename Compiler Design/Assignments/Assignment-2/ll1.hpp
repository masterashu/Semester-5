// Assumptions
// 1.Epsilon is entered as #
// 2.Each production is entered seperateley
// 3.No Left Recursion
// 4.Only Valid Inputs

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace parser {

typedef struct raw_production {
    char lhs, rhs[15];
} raw_prod;

typedef struct production {  // Structure for saving the productions
    char lhs, rhs[10], first[20], follow[20];
    int complete, epsilon;
} prod;

typedef struct table {
    char lhs, rhs[10];
} tab;

char terminals[100] = "";
int tc = 0;
raw_prod* rp;  // Raw Production
int rpc = 0;   // Raw Production Count
prod* p;       // Global variable declaration
tab** t;
int nt = 0, np = 0, nn = 0;
char start = 'S';

void Find_Epsilon()  // to find whether epsilon is present in the given
                     // production
{
    int i, j;
    for (i = nt; i < nt + np; i++) {
        for (j = 0; p[i].rhs[j] != '\0'; j++) {
            if (p[i].rhs[j] == '#') {
                p[i].epsilon = 1;
                break;
            }
        }
    }
}

int IsTerminal(char symbol) {
    return (symbol >= 'a' && symbol <= 'z');
}

char* Remove_Duplicates(char* first) {
    int i, j, k;
    for (i = 0; first[i] != '\0'; i++) {
        for (j = i + 1; first[j] != '\0'; j++) {
            if (first[i] == first[j]) {
                for (k = j; first[k] != '\0'; k++) {
                    first[k] = first[k + 1];
                }
                j--;
            }
        }
    }
    return first;
}

void Print_First() {
    int i;
    for (i = 0; i < nt + np; i++)
        printf("\nFirst[%c] is %s ", p[i].lhs, p[i].first);
}

void Print_Follow() {
    int i;
    for (i = nt; i < nt + np; i++)
        printf("\nFollow[%c] is %s ", p[i].lhs, p[i].follow);
}

void Print_Table() {
    int i, j;
    for (i = 0; i <= nt + 1; i++) {
        printf("\n");
        for (j = 0; j <= nn; j++) {
            if (i == 0 || j == 0)
                printf("\t%c    %3s", t[i][j].lhs, t[i][j].rhs);
            else if (t[i][j].lhs != '\0')
                printf("\t%c -> %3s", t[i][j].lhs, t[i][j].rhs);
            else
                printf("\t%c    %3s", t[i][j].lhs, t[i][j].rhs);
        }
    }
}

void Calculate_First()  // Calculating the First of the production
{
    int finish = 0, i, j, k, l;
    while (!finish) {
        finish = 1;
        for (i = nt; i < nt + np; i++) {
            if (p[i].complete == 1)
                continue;
            if (p[i].rhs[0] == '#') {
                p[i].first[0] = '#';
                p[i].complete = 1;
            } else
                for (j = 0; p[i].rhs[j] != '\0'; j++) {
                    int flag = 0, kflag = 1;
                    for (k = 0; k < nt + np; k++) {
                        if (p[i].rhs[j] == p[k].lhs && p[k].complete == 1) {
                            strcat(p[i].first, p[k].first);
                            char* c;
                            c = (char*)malloc(20 * sizeof(char));
                            c = Remove_Duplicates(p[i].first);
                            strcpy(p[i].first, c);
                        }
                        if (p[i].rhs[j] == p[k].lhs && p[k].complete == 0)
                            kflag = 0;
                        if (k + 1 == nt + np && kflag == 1)
                            break;
                    }
                    for (l = 0; p[i].first[l] != '\0'; l++) {
                        if (p[i].first[l] == '#') {
                            flag = 1;
                            if (p[i].rhs[0] != '\0') {
                                for (; p[i].first[l] != '\0'; l++) {
                                    p[i].first[l] = p[i].first[l + 1];
                                }
                            }
                            break;
                        }
                    }
                    if (flag == 1 && p[i].rhs[j + 1] != '\0') {
                        continue;
                    } else if (flag == 1 && p[i].rhs[j + 1] == '\0' &&
                               k < nt + np) {
                        p[i].complete = 1;
                        break;
                    } else if (flag == 0 && k < nt + np) {
                        p[i].complete = 1;
                        break;
                    } else {
                        memset(p[i].first, '\0', 20);
                        break;
                    }
                }
        }
        finish = 1;
        for (l = nt; l < nt + np; l++) {
            if (p[l].complete == 0) {
                finish = 0;
            }
        }
    }
    Print_First();
}

void Calculate_Follow() {
    int i, j, k, l, m;
    int finish = 0, flag = 0, lflag = 0;
    while (!finish) {
        finish = 1;
        for (i = nt; i < nt + np; i++) {
            lflag = 0, flag = 0;
            if (p[i].complete == 1) {
                continue;
            }
            if (p[i].lhs == start) {
                p[i].follow[0] = '$';
            }
            {
                for (j = 0; j < nt + np; j++) {
                    for (k = 0; p[j].rhs[k] != '\0'; k++) {
                        if (p[i].lhs == p[j].rhs[k] &&
                            p[j].rhs[k + 1] != '\0') {
                            for (l = 0; l < nt + np; l++) {
                                if (p[l].lhs == p[j].rhs[k + 1]) {
                                    flag = 0;
                                    strcat(p[i].follow, p[l].first);
                                    char* c;
                                    c = (char*)malloc(20 * sizeof(char));
                                    c = Remove_Duplicates(p[i].follow);
                                    strcpy(p[i].follow, c);
                                    for (m = 0; p[i].follow[m] != '\0'; m++) {
                                        if (p[i].follow[m] == '#') {
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag == 1) {
                                        for (; p[i].follow[m] != '\0'; m++) {
                                            p[i].follow[m] = p[i].follow[m + 1];
                                        }
                                    }
                                    if (flag == 1 && p[j].complete == 1) {
                                        strcat(p[i].follow, p[j].follow);
                                        char* c;
                                        c = (char*)malloc(20 * sizeof(char));
                                        c = Remove_Duplicates(p[i].follow);
                                        strcpy(p[i].follow, c);
                                    }
                                    if (flag == 1 && p[j].complete == 0 &&
                                        p[j].lhs != p[j].rhs[k]) {
                                        lflag = 1;
                                        memset(p[i].follow, '\0', 20);
                                        break;
                                    }
                                }
                            }
                        } else if (p[i].lhs == p[j].rhs[k] &&
                                   p[j].rhs[k + 1] == '\0') {
                            if (p[j].complete == 1) {
                                strcat(p[i].follow, p[j].follow);
                                char* c;
                                c = (char*)malloc(20 * sizeof(char));
                                c = Remove_Duplicates(p[i].follow);
                                strcpy(p[i].follow, c);
                            } else if (p[j].complete == 0 &&
                                       p[j].lhs != p[j].rhs[k]) {
                                lflag = 1;
                                memset(p[i].follow, '\0', 20);
                                break;
                            }
                        }
                        if (lflag == 1)
                            break;
                    }
                    if (lflag == 1)
                        break;
                    if (lflag == 0 && j + 1 == nt + np)
                        p[i].complete = 1;
                }
            }
        }
        finish = 1;
        for (l = nt; l < nt + np; l++) {
            if (p[l].complete == 0) {
                finish = 0;
            }
        }
    }
    Print_Follow();
}

void Create_Table() {
    int i, j, k, l, m, n, flag;
    t = (tab**)malloc((nt + 2) * sizeof(tab*));
    for (i = 0; i < (nt + 2); i++)
        t[i] = (tab*)malloc((np + 1) * sizeof(tab));
    for (i = 0; i <= nt + 1; i++) {
        for (j = 0; j <= np; j++) {
            t[i][j].lhs = '\0';
            memset(t[i][j].rhs, '\0', 10);
        }
    }
    for (i = 0; i < nt; i++) {
        t[i + 1][0].lhs = p[i].lhs;
    }
    t[i + 1][0].lhs = '$';
    for (i = 0, k = 0; i < np; i++) {
        flag = 0;
        for (j = 0; j < k; j++) {
            if (t[0][j + 1].lhs == p[nt + i].lhs)
                flag = 1;
        }
        if (flag == 1) {
            continue;
        } else {
            t[0][k + 1].lhs = p[nt + i].lhs;
            k++;
        }
    }
    nn = k;
    for (i = nt; i < nt + np; i++) {
        for (j = 0; j <= nn; j++) {
            if (t[0][j].lhs == p[i].lhs) {
                k = j;
                break;
            }
        }
        for (j = 0; p[i].first[j] != '\0'; j++) {
            if (p[i].first[j] != '#') {
                for (l = 0; l <= nt + 1; l++) {
                    if (t[l][0].lhs == p[i].first[j]) {
                        m = l;
                        break;
                    }
                }
                t[l][k].lhs = p[i].lhs;
                strcpy(t[l][k].rhs, p[i].rhs);
            } else {
                for (n = 0; p[i].follow[n] != '\0'; n++) {
                    for (l = 0; l <= nt + 1; l++) {
                        if (t[l][0].lhs == p[i].follow[n]) {
                            m = l;
                            break;
                        }
                    }
                    t[l][k].lhs = p[i].lhs;
                    strcpy(t[l][k].rhs, p[i].rhs);
                }
            }
        }
    }
    Print_Table();
}

void Ready() {
    rp = (raw_prod*)malloc(sizeof(raw_prod) * 1000);  // Preallocating memory
}

void AddProduction(char symbol, const char* rule) {
    int p_i = 1;
    raw_prod* raw_p = (rp + rpc++);
    raw_p->lhs = symbol;
    strcpy(raw_p->rhs, rule);
    for (int j = 0; j < strlen(rule); j++) {
        int already_present = 0;
        for (int t_i = 0; t_i < tc; t_i++) {
            if (rule[j] == terminals[t_i] || (!IsTerminal(rule[j]))) {
                already_present = 1;
            }
        }
        if (!already_present && IsTerminal(rule[j])) {
            printf("Adding terminal %c\n", rule[j]);
            terminals[tc++] = rule[j];
        }
    }
}

void Parse(int productionCount) {
    nt = tc;
    np = productionCount;
    int i;
    p = (prod*)(malloc((nt + np + 1) *
                       sizeof(prod)));  // Allocating the memory for structures
    for (i = 0; i < nt + np + 1; i++) {
        memset(p[i].first, '\0', 20);
        memset(p[i].follow, '\0', 20);
        memset(p[i].rhs, '\0', 10);
        p[i].lhs = '\0';
        p[i].complete = 0;
        p[i].epsilon = 0;
    }
    // Reading the terminals and storing the first & follow of terminals
    printf("\nINFO: the number of terminals: %d", nt);
    printf("\nINFO: the number of productions: %d", np);
    printf("\nINFO: the start production: %c\n", start);
    for (i = 0; i < nt; i++) {
        char sym = terminals[i];
        p[i].lhs = sym;
        p[i].rhs[0] = sym;
        p[i].first[0] = sym;
        p[i].follow[0] = sym;
        p[i].complete = 1;
    }

    for (int j = 0; i < nt + np; i++,
             j++)  // Reading the lefthand and righthand side of the productions
    {
        p[i].lhs = rp[j].lhs;
        strcpy(p[i].rhs, rp[j].rhs);
    }
    Find_Epsilon();
    Calculate_First();  // Calculating the first of the productions
    for (i = nt; i < nt + np; i++) {
        p[i].complete = 0;
    }
    Calculate_Follow();  // Calculating the follow of the productions
    Create_Table();
}
}  // namespace parser