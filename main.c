#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int ind_open_bracket = 0, ind_close_bracket = 0, ind_last_num_elm = 0,
        ind_first_num_elm = 0, ind_second_num_elm = 0, error = 0;
    // Open file, if couldn't - output mistake
    FILE* file1;
    file1 = fopen("Input.txt", "r");
    if (!file1) {
        printf("Error: cannot open file. Check name of file \n");
        return 1;
    }

    int length = 0, element = 0;
    while (true) {
        element = fgetc(file1);
        if (element == EOF)
            if (feof(file1) != 0)
                break;
        length++;
    }

    fclose(file1);

    char b[] = "circle";
    char c[] = "CIRCLE";
    char* a;
    a = (char*)(malloc(length * sizeof(char)));
    FILE* file;
    file = fopen("Input.txt", "r");

    if (length == 0)
        return 1;

    int i;
    while (fgets(a, length + 1, file)) {
        printf("%s", a);

        for (i = 0; i < 7; i++) {
            if (a[i] != b[i] && a[i] != c[i] && i < 6) {
                printf("Error at column %d: expected 'circle'\n", i);
                error = 1;
                break;
            }
            ind_open_bracket = i;
        }

        for (i = 0; i < length; i++) {
            if (a[i] == ')')
                ind_close_bracket = i;
            else
                ind_close_bracket = length - 1;
        }
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
            } else
                break;
        }

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
            } else
                break;
        }

        for (i = ind_second_num_elm + 3; i < ind_close_bracket; i++) {
            if (error == 0) {
                if (isdigit(a[i]) == 0 && a[i] != '.') {
                    if (a[i] == ')' || a[i] == '(' || a[i] == ' ')
                        break;
                    error = 1;
                    printf("Error at column %d: expected '<double>'\n", i);
                    break;
                }
                ind_last_num_elm = i;
            } else
                break;
        }

        for (i = ind_last_num_elm + 1; i < length; i++) {
            if (error == 0) {
                if (a[i] != ')') {
                    error = 1;
                    printf("Error at column %d: expected ')'\n", i);
                } else
                    ind_close_bracket = i;
                break;
            } else
                break;
        }

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

        if (error == 0)
            printf("No Errors!\n");
        error = 0;
        printf("\n");
    }
    return 0;
}