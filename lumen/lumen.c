#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LIGHTS 0
#define CANDLE 1

typedef struct {
    int light;
    bool candle;
} spot;

void dump(spot **map, int len)
{
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++) {
            char c = ' ';
            if (map[i][j].candle)
                c = 'C';
            fprintf(stderr, "%d[%c]   ", map[i][j].light, c);
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
}

void enlight_once(spot **map, int map_max_len, int x_center, int y_center, int len, int intensity)
{
    int x0 = x_center - (len-1)/2;
    int y0 = y_center - (len-1)/2;
    int max = len-1;
    
    for (int i=0; i<=max; i++) {
        int coordX = x0 + i;
        if (coordX < 0 || coordX >= map_max_len) // X out of map
            continue;
        
        for (int j=0; j<=max; j++) {
            int coordY = y0 + j;
            if (coordY < 0 || coordY >= map_max_len) // Y out of map
                continue;

            if (coordX != x_center || coordY != y_center) {
                if (!map[coordX][coordY].candle && map[coordX][coordY].light < intensity)
                    map[coordX][coordY].light++;
            }
        }
    }
}

void enlighten(spot **map, int map_max_len, int x_center, int y_center, int intensity)
{
    for (int i=1; i<intensity; i++)
        enlight_once(map, map_max_len, x_center, y_center, 2*i+1, intensity);
}

void light_on_candles(spot **map, int N, int base_light_intensity)
{
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (map[i][j].candle) {
                map[i][j].light = base_light_intensity;
                enlighten(map, N, i, j, base_light_intensity);
            }
        }
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    int L;
    scanf("%d", &L); fgetc(stdin);

    // allocating map
    spot **map = malloc(N*sizeof(spot *));
    for (int i=0; i<N; i++) {
        map[i] = malloc(N*sizeof(spot));
    }

    for (int i=0; i<N; i++) {
        char line[501];
        fgets(line, 501, stdin);

        int k=0;
        for (int j=0; j<501; j++) {
            switch (line[j]) {
                case ' ':
                    continue;
                    break;
                case 'X':
                    map[i][k].candle = false;
                    break;
                case 'C':
                    map[i][k].candle = true;
                    break;
                case '\0':
                    break;
            }
            k++;
        }
    }

    light_on_candles(map, N, L);

    // count spots with empty lights
    int cnt = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            if (map[i][j].light == 0)
                cnt++;
        }
    }
    printf("%d\n", cnt);

    // Freeing map
    for (int i=0; i<N; i++)
        free(map[i]);
    free(map);

    return 0;
}