#include <stdio.h>
#include <string.h>
char find_empty(int dict_counter[]);

int main() {
    char dict[26][10][20];
    int dict_counter[26];
    for (int i = 0; i < 26; i++) {
        dict_counter[i] = 0;
    }

    char production[20];
    int num_of_pd = 2;
    int start_index = 3;
    char key;
    for (int i = 0; i < num_of_pd; i++) {
        scanf("%s", production);
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

    for (int i = 0; i < 26; i++) {
        if (dict_counter[i] > 0) {
            for (int j = 0; j < dict_counter[i]; j++) {
                if (dict[i][j][0] == i + 'A') {
                    char ekey = find_empty(dict_counter);
                    // printf("Key %c\n",ekey);

                    for (int k = 0; k < dict_counter[i]; k++) {
                        // printf("Before string: %s\n",dict[i][k]);
                        int len = strlen(dict[i][k]);
                        dict[i][k][len] = ekey;
                        dict[i][k][len + 1] = '\0';
                        // printf("After string: %s\n",dict[i][k]);

                        if (dict[i][k][0] == i + 'A') {
                            // printf("Before remove: %s\n",dict[i][k]);
                            memmove(dict[i][k], dict[i][k] + 1,
                                    strlen(dict[i][k]));
                            // printf("After remove: %s\n",dict[i][k]);
                            strcpy(dict[ekey - 'A'][dict_counter[ekey - 'A']++],
                                   dict[i][k]);
                            // printf("%c -> %s\n",ekey, dict[i][k]);
                            strcpy(dict[i][k], " ");
                        }
                    }
                    int k = 0;
                    int l = dict_counter[i] - 1;
                    // printf("1.dict counter i = %d\n",dict_counter[i]);
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
                    // printf("2.dict counter i = %d\n",dict_counter[i]);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (dict_counter[i] > 0) {
            printf("%c->", i + 'A');
            for (int j = 0; j < dict_counter[i]; j++) {
                printf("%s|", dict[i][j]);
            }
            printf("\n");
        }
    }

    // for(int i=0;i<num;i++){
    //     printf("\nGRAMMAR : : : %s",production[i])
    //     non_terminal=production[i][0];

    //     if(non_terminal==production[i][index]) {
    //         alpha=production[i][index+1];
    //         printf(" is left recursive.\n");

    //         while(production[i][index]!=0 && production[i][index]!='|')
    //             index++;
    //         if(production[i][index]!=0) {
    //             beta=production[i][index+1];
    //             printf("Grammar without left recursion:\n");
    //             printf("%c->%c%c\'",non_terminal,beta,non_terminal);
    //             printf("\n%c\'->%c%c\'|E\n",non_terminal,alpha,non_terminal);
    //         }
    //         else
    //         printf(" can't be reduced\n");
    //     }
    //     else
    //         printf(" is not left recursive.\n");
    //     index=3;
    // }
}

char find_empty(int dict_counter[]) {
    for (int i = 25; i >= 0; i--)
        if (dict_counter[i] == 0)
            return (char)(i + 'A');
}
