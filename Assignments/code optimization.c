
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct expr {
    char l;      
    char r[20]; 
} op[10], pr[10];

int main() {
    int n, i, j, z = 0;
    char temp, *p;

    printf("Enter the number of expressions: ");
    scanf("%d", &n);

    printf("Enter the expressions (e.g., a=b+c):\n");
    for (i = 0; i < n; i++) {
        printf("%d: ", i + 1);
        scanf(" %c=%s", &op[i].l, op[i].r);
    }

    printf("\nIntermediate Code:\n");
    for (i = 0; i < n; i++)
        printf("%c=%s\n", op[i].l, op[i].r);

    for (i = 0; i < n; i++) {
        temp = op[i].l;

        for (j = i + 1; j < n; j++) {
            p = strchr(op[j].r, temp);
            if (p) {
                pr[z].l = op[i].l;
                strcpy(pr[z].r, op[i].r);
                z++;
                break;
            }
        }
    }

    printf("\nOptimized Code (After Reduction):\n");
    for (i = 0; i < z; i++)
        printf("%c=%s\n", pr[i].l, pr[i].r);

    return 0;
}
