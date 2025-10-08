#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    char expr[50];
    char symbols[20];
    void *addresses[20];
    int i = 0, count = 0;
    char c;

    printf("Enter expression ending with $: ");
    while ((c = getchar()) != '$' && i < sizeof(expr) - 1)
        expr[i++] = c;
    expr[i] = '\0';

    printf("\nGiven Expression: %s\n", expr);
    printf("\nSymbol\tAddress\t\tType\n");

    for (i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];
        if (isspace(ch)) continue;

        addresses[count] = malloc(sizeof(char));
        symbols[count] = ch;

        if (isalpha(ch))
            printf("%c\t%p\tidentifier\n", ch, addresses[count]);
        else if (isdigit(ch))
            printf("%c\t%p\tconstant\n", ch, addresses[count]);
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '=')
            printf("%c\t%p\toperator\n", ch, addresses[count]);

        count++;
    }
    return 0;
}
