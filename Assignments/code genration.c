#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int labels[20];
int labelCount = 0;

// Check if label already exists
int check_label(int k) {
    for (int i = 0; i < labelCount; i++) {
        if (k == labels[i])
            return 1;
    }
    return 0;
}

int main() {
    FILE *fpIn, *fpOut;
    char filename[20], op[10], ch;
    char operand1[8], operand2[8], result[8];
    int i = 0;

    printf("Enter the filename of the intermediate code: ");
    scanf("%s", filename);

    fpIn = fopen(filename, "r");
    fpOut = fopen("target.txt", "w");

    if (!fpIn || !fpOut) {
        printf("Error opening file.\n");
        exit(1);
    }

    while (fscanf(fpIn, "%s", op) != EOF) {
        fprintf(fpOut, "\n");
        i++;

        if (check_label(i))
            fprintf(fpOut, "label#%d\n", i);

        // Print statement
        if (strcmp(op, "print") == 0) {
            fscanf(fpIn, "%s", result);
            fprintf(fpOut, "\tOUT %s\n", result);
        }

        // Goto statement
        else if (strcmp(op, "goto") == 0) {
            fscanf(fpIn, "%s %s", operand1, operand2);
            fprintf(fpOut, "\tJMP %s, label#%s\n", operand1, operand2);
            labels[labelCount++] = atoi(operand2);
        }

        // Array assignment
        else if (strcmp(op, "[]=") == 0) {
            fscanf(fpIn, "%s %s %s", operand1, operand2, result);
            fprintf(fpOut, "\tSTORE %s[%s], %s\n", operand1, operand2, result);
        }

        // Unary minus
        else if (strcmp(op, "uminus") == 0) {
            fscanf(fpIn, "%s %s", operand1, result);
            fprintf(fpOut, "\tLOAD -%s, R1\n", operand1);
            fprintf(fpOut, "\tSTORE R1, %s\n", result);
        }

        // Operators and relational conditions
        else {
            switch (op[0]) {
                case '*':
                    fscanf(fpIn, "%s %s %s", operand1, operand2, result);
                    fprintf(fpOut, "\tLOAD %s, R0\n\tLOAD %s, R1\n\tMUL R1, R0\n\tSTORE R0, %s\n", operand1, operand2, result);
                    break;

                case '+':
                    fscanf(fpIn, "%s %s %s", operand1, operand2, result);
                    fprintf(fpOut, "\tLOAD %s, R0\n\tLOAD %s, R1\n\tADD R1, R0\n\tSTORE R0, %s\n", operand1, operand2, result);
                    break;

                case '-':
                    fscanf(fpIn, "%s %s %s", operand1, operand2, result);
                    fprintf(fpOut, "\tLOAD %s, R0\n\tLOAD %s, R1\n\tSUB R1, R0\n\tSTORE R0, %s\n", operand1, operand2, result);
                    break;

                case '/':
                    fscanf(fpIn, "%s %s %s", operand1, operand2, result);
                    fprintf(fpOut, "\tLOAD %s, R0\n\tLOAD %s, R1\n\tDIV R1, R0\n\tSTORE R0, %s\n", operand1, operand2, result);
                    break;

                case '%':
                    fscanf(fpIn, "%s %s %s", operand1, operand2, result);
                    fprintf(fpOut, "\tLOAD %s, R0\n\tLOAD %s, R1\n\tDIV R1, R0\n\tSTORE R0, %s\n", operand1, operand2, result);
                    break;

                case '=':
                    fscanf(fpIn, "%s %s", operand1, result);
                    fprintf(fpOut, "\tSTORE %s, %s\n", operand1, result);
                    break;

                case '>':
                    fscanf(fpIn, "%s %s %s", operand1, operand2, result);
                    fprintf(fpOut, "\tLOAD %s, R0\n\tJGT %s, label#%s\n", operand1, operand2, result);
                    labels[labelCount++] = atoi(result);
                    break;

                case '<':
                    fscanf(fpIn, "%s %s %s", operand1, operand2, result);
                    fprintf(fpOut, "\tLOAD %s, R0\n\tJLT %s, label#%s\n", operand1, operand2, result);
                    labels[labelCount++] = atoi(result);
                    break;
            }
        }
    }

    fclose(fpIn);
    fclose(fpOut);

    // Display generated target code
    fpOut = fopen("target.txt", "r");
    if (!fpOut) {
        printf("Error opening target.txt\n");
        exit(1);
    }

    printf("\nGenerated Target Code:\n");
    while ((ch = fgetc(fpOut)) != EOF)
        putchar(ch);

    fclose(fpOut);
    return 0;
}
