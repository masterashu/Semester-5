#include <cstdio>
#include <cstring>
#include <vector>
#include "left_factoring.hpp"

namespace left_recursion {
char dict[26][10][20];
int dict_counter[26] = {0};
char production[20];
int num_of_pd = 2;
int start_index = 3;
char key;

char find_empty(int dict_counter[]) {
    for (int i = 25; i >= 0; i--)
        if (dict_counter[i] == 0)
            return (char)(i + 'A');
    return 0;
}

void AddProduction(char* production, int length) {
    key = production[0];
    char* token = strtok(production, "|");

    while (token != NULL) {
        strcpy(dict[key - 'A'][dict_counter[key - 'A']++], token);
        token = strtok(NULL, "|");
    }
    for (int i = 3; i < strlen(dict[key - 'A'][0]); i++) {
        dict[key - 'A'][0][i - start_index] = dict[key - 'A'][0][i];
    }
    dict[key - 'A'][0][strlen(dict[key - 'A'][0]) - start_index] = '\0';
}

int RemoveRecursion(vector<left_factoring::Production>& Grammar) {
    try {
        for (int i = 0; i < 26; i++) {
            if (dict_counter[i] > 0) {
                for (int j = 0; j < dict_counter[i]; j++) {
                    if (dict[i][j][0] == i + 'A') {
                        char ekey = find_empty(dict_counter);
                        // printf("Key %c\n", ekey);

                        for (int k = 0; k < dict_counter[i]; k++) {
                            // printf("Before string: %s\n", dict[i][k]);
                            int len = strlen(dict[i][k]);
                            dict[i][k][len] = ekey;
                            dict[i][k][len + 1] = '\0';
                            // printf("After string: %s\n", dict[i][k]);

                            if (dict[i][k][0] == i + 'A') {
                                // printf("Before remove: %s\n", dict[i][k]);
                                memmove(dict[i][k], dict[i][k] + 1,
                                        strlen(dict[i][k]));
                                // printf("After remove: %s\n", dict[i][k]);
                                strcpy(dict[ekey - 'A']
                                           [dict_counter[ekey - 'A']++],
                                       dict[i][k]);
                                strcpy(dict[i][k], " ");
                            }
                        }
                        int k = 0;
                        int l = dict_counter[i] - 1;
                        // printf("1.dict counter i = %d\n", dict_counter[i]);
                        while (k < l) {
                            if (strcmp(dict[i][k], " ") == 0) {
                                strcpy(dict[i][k], dict[i][l]);
                                strcpy(dict[i][l], " ");
                                l--;
                                dict_counter[i]--;
                            }
                            k++;
                        }
                        dict_counter[i];
                        // printf("2.dict counter i = %d\n", dict_counter[i]);
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < 26; i++) {
            if (dict_counter[i] > 0) {
                // printf("%c->", i + 'A');
                for (int j = 0; j < dict_counter[i]; j++) {
                    // printf("%s|", dict[i][j]);
                    string production = "";
                    // printf("%c dict: %s\n", (char)(i + 'A'), dict[i][j]);
                    production += (char)(i + 'A');
                    if (dict[i][j][0] != '-') {
                        production += string("->");
                    }
                    if (string(dict[i][j]) != " ") {
                        production += string(dict[i][j]);
                        left_factoring::AddProduction(
                            production, production.length(), Grammar);
                    }
                }
                // printf("\n");
            }
        }
    } catch (...) {
        printf("Cannot remove Left Recursion.");
        return -1;
    }
    return 0;
}
}  // namespace left_recursion
