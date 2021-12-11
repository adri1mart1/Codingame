#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 3000

void print_tab(int tab[])
{
    int i=0;
    while (tab[i] > 0) 
        fprintf(stderr, "%d ", tab[i++]);
    fprintf(stderr, "\n");
}

int main()
{
    int tab1[MAX_SIZE] = {0}; // the line to analyze
    int tab2[MAX_SIZE] = {0}; // the line to be build up depending on the line to analyze

    scanf("%d", &tab1[0]);
    int L;
    scanf("%d", &L);

    for (int i=1; i<L; i++) {
        // print_tab(tab1);

        int j = 1;
        int prev = tab1[0];
        int cnt = 1;
        int x = 0;

        while (tab1[j] > 0) {
            if (tab1[j] == prev) {
                cnt++;
            } else {
                tab2[x++] = cnt;
                tab2[x++] = prev;
                cnt = 1;
                prev = tab1[j];
            }
            j++;
        }
        tab2[x++] = cnt;
        tab2[x++] = prev;

        memcpy(tab1, tab2, MAX_SIZE*sizeof(int));
    }

    int i = 0;
    do {
        if (i > 0) 
            printf(" ");
        printf("%d", tab1[i++]);
    } while (tab1[i] > 0);

    putchar('\n');

    return 0;
}