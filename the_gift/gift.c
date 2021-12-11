#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int budgets[1000000];

int cmp(const void *a, const void *b) {
   return (*(int *)a - *(int *)b);
}

void divide_budget(int n, int c)
{
    int sum = 0;
    for (int i=0; i<n; i++)
        sum += budgets[i];
    
    if (sum < c) {
        printf("IMPOSSIBLE\n");
        return;
    }

    qsort(budgets, n, sizeof(int), cmp);

    int pp = c / n; // price per person

    for (int i=0; i<n-1; i++) {
        if (pp > budgets[i]) {
            printf("%d\n", budgets[i]);
            c -= budgets[i];
        } else {
            printf("%d\n", pp);
            c -= pp;
        }

        pp = c / (n-i-1);
    }
    
    printf("%d\n", c); // last budget to be paid
}

int main()
{
    int n;
    scanf("%d", &n);
    int c;
    scanf("%d", &c);
    for (int i = 0; i < n; i++) {
        int b;
        scanf("%d", &b);
        budgets[i] = b;
    }

    divide_budget(n, c);

    return 0;
}