#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE* file1;
    FILE* file;

    file1 = fopen("test.txt", "r");

    if (!file1) { 
        printf("Error: cannot open file. Check name of file\n");
    }

    int i, ind_open_bracket = 0, ind_close_bracket = 0, ind_last_num_elm = 0,
           ind_first_num_elm = 0, ind_second_num_elm = 0;
    int length = 0, count = 0, element = 0, error = 0;

    while (1) {
        element = fgetc(file1);
        if (element == EOF) {
            if (feof(file1) != 0) {
                break;
            }
        }
        count++;
    }
    length = count;
    fclose(file1);

    char a[length], b[6] = "circle";
    file = fopen("test.txt", "r");
    while (fgets(a, length + 1, file)) {
        printf("%s", a);

        // check 'circle and finding index of '(' symbol
        for (i = 0; i < 7; i++) {
            if (a[i] != b[i] && i < 6) {
                printf("Error at column %d: expected 'circle'\n", i);
                error = 1;
                break;
                ;
            }
            ind_open_bracket = i;
        }
        // printf("'(' = %d\n", ind_open_bracket);

        for (i = 0; i < length; i++) {
            if (a[i] == ')') {
                ind_close_bracket = i;
            } else {
                ind_close_bracket = length - 1;
            }
        }

        // check first number
        for (i = ind_open_bracket + 1; a[i] != ' '; i++) {
            if (error == 0) {
                if (a[i] == ',') {
                    error = 1;
                    printf("Error at column %d: expected '<space>' and "
                           "'<double>'\n",
                           i);
                    break;
                }
                if (isdigit(a[i]) == 0 && a[i] != '.') {
                    error = 1;
                    printf("Error at column %d: expected '<double>'\n", i);
                    break;
                }
                ind_first_num_elm = i;
            } else {
                break;
            }
        }
        // printf("index of first numer = %d\n", ind_first_num_elm);

        // check second number
        for (i = ind_first_num_elm + 2; a[i] != ','; i++) {
            if (error == 0) {
                if (a[i] == ')') {
                    error = 1;
                    printf("Error at column %d: expected ',' and '<double>'\n",
                           i);
                    break;
                }
                if (isdigit(a[i]) == 0 && a[i] != '.') {
                    error = 1;
                    printf("Error at column %d: expected '<double>'\n", i);
                    break;
                }
                ind_second_num_elm = i;
            } else {
                break;
            }
        }
        // printf("index of second number = %d\n", ind_second_num_elm);

        // check last number
        for (i = ind_second_num_elm + 3; i < ind_close_bracket; i++) {
            if (error == 0) {
                if (isdigit(a[i]) == 0 && a[i] != '.') {
                    if (a[i] == ')' || a[i] == '(' || a[i] == ' ') {
                        break;
                    }
                    error = 1;
                    printf("Error at column %d: expected '<double>'\n", i);
                    break;
                }
                ind_last_num_elm = i;
            } else {
                break;
            }
        }
        // printf("index of last number = %d\n", ind_last_num_elm);

        // check ')' symbol
        for (i = ind_last_num_elm + 1; i < length; i++) {
            if (error == 0) {
                if (a[i] != ')') {
                    error = 1;
                    printf("Error at column %d: expected ')'\n", i);
                    break;
                } else {
                    ind_close_bracket = i;
                    break;
                }
            } else {
                break;
            }
        }
        // printf("')' = %d\n", ind_close_bracket);

        // check unexpected tokens
        for (i = ind_close_bracket + 1; i < length; i++) {
            if (error == 0) {
                if (a[i] == '\n') {
                    break;
                }

                if (a[i] != ' ') {
                    error = 1;
                    printf("Error at column %d: unexpected token\n", i);
                    break;
                }
            } else {
                break;
            }
        }

        if (error == 0) {
            printf("No Errors!\n");
        }

        error = 0;
        printf("\n");
    }
    return 0;
}