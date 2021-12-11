#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int s[9][9];
static int a[10];

int check() {

    // checking lines
    for (int i=0; i<9; i++) {
        memset(a, 0, sizeof(a));
        for (int j=0; j<9; j++) {
            if (a[s[i][j]]) return -1;
            a[s[i][j]]++;
        }
    }

    // checking columns
    for (int i=0; i<9; i++) {
        memset(a, 0, sizeof(a));
        for (int j=0; j<9; j++) {
            if (a[s[j][i]]) return -1;
            a[s[j][i]]++;
        }
    }

    // checking squares
    for (int i=0; i<3; i++) {
        for (int j=0; j<3; j++) {
            memset(a, 0, sizeof(a));
            for (int x=0; x<3; x++) {
                for (int y=0; y<3; y++) {
                    if (a[s[3*i+x][3*j+y]]) return -1;
                    a[s[3*i+x][3*j+y]]++;
                }
            }
        }
    }
    return 0;
}

void main()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            scanf("%d", &s[i][j]);
    }

    if (check() == 0)
        printf("true\n");
    else
        printf("false\n");
}