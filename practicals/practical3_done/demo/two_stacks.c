#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: %s <expression_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) return 1;

    StackPtr ops = StackInit();
    StackPtr vals = StackInit();
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '(' || isspace(ch)) {
            continue;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            char* op = (char*)malloc(sizeof(char));
            *op = (char)ch;
            push(ops, op);
        } else if (ch == ')') {
            char* op = (char*)pop(ops);
            double* v2 = (double*)pop(vals);
            double* v1 = (double*)pop(vals);
            double* res = (double*)malloc(sizeof(double));

            if (*op == '+') *res = *v1 + *v2;
            else if (*op == '-') *res = *v1 - *v2;
            else if (*op == '*') *res = *v1 * *v2;
            else if (*op == '/') *res = *v1 / *v2;

            push(vals, res);
            free(op); free(v1); free(v2);
        } else if (isdigit(ch)) {
            ungetc(ch, file);
            double* val = (double*)malloc(sizeof(double));
            fscanf(file, "%lf", val);
            push(vals, val);
        }
    }

    double* result = (double*)pop(vals);
    if (result) {
        printf("Result: %.2f\n", *result);
        free(result);
    }

    StackDestroy(ops);
    StackDestroy(vals);
    fclose(file);
    return 0;
}