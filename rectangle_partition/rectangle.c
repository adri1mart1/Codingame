#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* This program is based on two simple tables build with:
 *  - index 0
 *  - size N 
 *  - all lines
 * The example will lead to [0; 2; 5; 10] for X axis and
 * [0; 3; 5] for Y axis
 *
 * Then, is the table is size N, all possible additions in
 * this table are N(N+1)/2 which is equivalent formula for
 * 1+2+3+4+..+n
 *
 * A table is dynamically allocated with all initial values
 * plus any possible additions
 * The example will be for X-axis:
 * [0; 2; 5; 10; 2; 5; 10; 3; 8; 5]
 *               |                |
 *               this part being all
 *               possibles square length
 * And for Y-axis:
 * [0; 3; 5; 3; 5; 2]
 *           |     |
 *
 * For hi-density tests, a little optimization is needed so
 * all the possible-square-length part is sorted 
 *
 * Final step is just to compare all common length on X and
 * Y axis to find squares count. Thanks to sorted table, the
 * comparison is fast enough to fullfil requirements
 */

void print_tab(int *tab, int s) {
    for (int i=0; i<s; i++)
        fprintf(stderr, "%d ", tab[i]);
    fprintf(stderr, "\n");
}

void prepare(int *tab, int start, int end) {
    int current = end;
    for (int i=0; i<end; i++) {
        for (int j=i+1; j<end; j++) {
            tab[current] = tab[j] - tab[i];
            current++;          
        }
    }
}

int count_squares(int *t1, int s1, int *t2, int s2)
{
    int cnt = 0;
    for (int i=0; i<s1; i++) {
        for (int j=0; j<s2; j++) {
            if (t1[i] < t2[j])
                break;
            if (t1[i] == t2[j])
                cnt++;
        }
    }
    return cnt;
}

static inline int compare(void const *a, void const *b)
{
   int const *pa = a;
   int const *pb = b;
   return *pa - *pb;
}

int main()
{
    int w;
    int h;
    int count_x, tot_cnt_x;
    int count_y, tot_cnt_y;
    scanf("%d%d%d%d", &w, &h, &count_x, &count_y);
    tot_cnt_x = count_x + 2;
    tot_cnt_y = count_y + 2;
    
    int tab_x_size = tot_cnt_x*(tot_cnt_x + 1) / 2;
    int *tab_x = calloc(tab_x_size, sizeof(int));
    int tab_y_size = tot_cnt_y*(tot_cnt_y + 1) / 2;
    int *tab_y = calloc(tab_y_size, sizeof(int));

    for (int i = 1; i <= count_x; i++) {
        int x;
        scanf("%d", &x);
        tab_x[i] = x;
    }
    tab_x[count_x+1] = w;

    for (int i = 1; i <= count_y; i++) {
        int y;
        scanf("%d", &y);
        tab_y[i] = y;
    }
    tab_y[count_y+1] = h;

    prepare(tab_x, 0, tot_cnt_x);
    prepare(tab_y, 0, tot_cnt_y);

    //print_tab(tab_x, tab_x_size);
    //print_tab(tab_y, tab_y_size);

    qsort(tab_x + tot_cnt_x, tab_x_size - tot_cnt_x, sizeof(int), compare);
    qsort(tab_y + tot_cnt_y, tab_y_size - tot_cnt_y, sizeof(int), compare);

    //print_tab(tab_x, tab_x_size);
    //print_tab(tab_y, tab_y_size);

    printf("%d\n", count_squares(tab_x + tot_cnt_x, tab_x_size - tot_cnt_x, tab_y + tot_cnt_y, tab_y_size - tot_cnt_y));

    free(tab_x);
    free(tab_y);

    return 0;
}