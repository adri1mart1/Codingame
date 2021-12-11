#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void increase(char c, int *v, int *min, int *max)
{
    *min = (*v)+1;
    if (*v < (*max)-2)
        (*v) += (int) ceil((double)(((double)(*max) - (double)(*v))/2));
    else
        (*v)++;
}

void decrease(char c, int *v, int *min, int *max)
{
    *max = (*v)-1;
    if (*v > (*min)+2)
        (*v) -= (int) ceil((double)(((double)(*v) - (double)(*min))/2));     
    else
        (*v)--;
}

void move_batman(int *x , int *y, char dir[], int *x_min, int *x_max, int *y_min, int *y_max)
{
    switch (dir[0]) {
        case 'U':
            decrease('y', y, y_min, y_max);
            if (dir[1] == 'R')
                increase('x', x, x_min, x_max);
            else if (dir[1] == 'L')
                decrease('x', x, x_min, x_max);
            break;

        case 'R':
            increase('x', x, x_min, x_max);
            break;

        case 'D':
            increase('y', y, y_min, y_max);
            if (dir[1] == 'R')
                increase('x', x, x_min, x_max);
            else if (dir[1] == 'L')
                decrease('x', x, x_min, x_max);
            break;

        case 'L':
            decrease('x', x, x_min, x_max);
            break;
    };
}

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    scanf("%d%d", &W, &H);
    
    int N; // maximum number of turns before game over.
    scanf("%d", &N);

    int X0, Y0;
    scanf("%d%d", &X0, &Y0);
    int x = X0, y = Y0;
    int x_min = 0, x_max = W;
    int y_min = 0, y_max = H;

    while (1) {
        // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        char bomb_dir[4];
        scanf("%s", bomb_dir);

        move_batman(&x, &y, bomb_dir, &x_min, &x_max, &y_min, &y_max);

        printf("%d %d\n", x, y);
    }

    return 0;
}