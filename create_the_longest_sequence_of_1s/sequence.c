#include <stdlib.h>
#include <stdio.h>

#define MAX 1000

static char b[MAX];

void check(int *max, int *cb, int *ca)
{
    int t = *ca + *cb + 1;

    if (t > *max)
        *max = t;

    *cb = *ca;
    *ca = 0;
}

int count() {
    int cb, ca, mv;
    cb = ca = mv = 0;

    for (int i=0; i<MAX; i++) {
        if (b[i] == 0) break;

        if (b[i] == '1')
            ca++;
        else
            check(&mv, &cb, &ca);
    }
    check(&mv, &cb, &ca);
    return mv;
}

void main() {
    scanf("%[^\n]", b);
    printf("%d\n", count());
}