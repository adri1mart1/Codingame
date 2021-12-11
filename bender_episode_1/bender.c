#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROW_SIZE 102

typedef enum {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
} Direction;

char *DirStr[] = {
    "NORTH",
    "EAST",
    "SOUTH",
    "WEST"
};

Direction prio_dir1[] = {
    SOUTH,
    EAST,
    NORTH,
    WEST
};

Direction prio_dir2[] = {
    WEST,
    NORTH,
    EAST,
    SOUTH
};

typedef struct {
    int x;
    int y;
    Direction dir;
    Direction prev_dir;
    Direction *priorities;
    bool breaker_mode;
} Bender_t;

#define ENDGAME 10000
static int moves_idx = 0;
static char moves[ENDGAME][6] = {0};

void init(Bender_t *b, int w, int h, char map[h][w])
{
    for (int i=0; i<w; i++) {
        for (int j=0; j<h; j++) {
            if (map[i][j] == '@') {
                b->x = j;
                b->y = i;
                i = w; // trick to exit loop
                break;
            }
        }
    }
    b->dir = SOUTH;
    b->prev_dir = SOUTH;
    b->breaker_mode = false;
    b->priorities = prio_dir1;
}

#if 0
void display(const int w, const int h, const char map[h][w])
{
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++)
            fprintf(stderr, "%c", map[i][j]);
        fprintf(stderr, "\n");
    }
}
#endif

void switch_priorities(Bender_t *b)
{
    if (b->priorities == prio_dir1)
        b->priorities = prio_dir2;
    else
        b->priorities = prio_dir1;
}

bool detect_obstacles(Bender_t *b, int w, int h, char map[h][w]) 
{
    int x = b->x;
    int y = b->y;

    switch (b->dir) {
        case NORTH: y--; break;
        case SOUTH: y++; break;
        case EAST:  x++; break;
        case WEST:  x--; break;
    }

    if (map[y][x] == '#')
        return true;
    if (map[y][x] == 'X') {
        if (b->breaker_mode) {
            map[y][x] = ' '; // clear obstacle
            return false;
        } else
            return true;
    }
    return false;
}

void change_dir(Bender_t *b, Direction d)
{
    b->prev_dir = b->dir;
    b->dir = d;
}

void teleport(Bender_t *b, int w, int h, char map[h][w])
{
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            if (map[i][j] == 'T' && (b->x != j || b->y != i)) {
                b->x = j;
                b->y = i;
                return;
            }
        }
    }
}

bool play(Bender_t *b, int w, int h, char map[h][w]) 
{
    switch (map[b->y][b->x]) {
        case ' ':
        case '@':
            break;
        case '$':
            return false;
            break;
        case 'S':
            change_dir(b, SOUTH);
            break;
        case 'E':
            change_dir(b, EAST);
            break;
        case 'W':
            change_dir(b, WEST);
            break;
        case 'N':
            change_dir(b, NORTH);
            break;
        case 'I':
            switch_priorities(b);
            break;
        case 'T':
            teleport(b, w, h, map);
            break;
        case 'B':
            b->breaker_mode = !b->breaker_mode;
            break;
    }

    if (detect_obstacles(b, w, h, map)) {
        Direction *d = b->priorities;
        for (int i=0; i<4; i++) {
            b->dir = *d;
            if (detect_obstacles(b, w, h, map) == false)
                break;
            d++;
        }
    }

    return true;
}

void move(Bender_t *b)
{
    strcpy(moves[moves_idx++], DirStr[b->dir]);

    switch (b->dir) {
        case NORTH: b->y--; break;
        case SOUTH: b->y++; break;
        case EAST:  b->x++; break;
        case WEST:  b->x--; break;
    }
}

int main()
{
    Bender_t bender;

    int w, h;
    scanf("%d%d", &h, &w); fgetc(stdin);

    char map[h][w];
    memset(map, 0, h*w*sizeof(char));
    for (int i=0; i<h; i++) {
        char row[MAX_ROW_SIZE] = {0};
        fgets(row, MAX_ROW_SIZE, stdin);
        memcpy(map[i], row, w); // trim \n
    }

    init(&bender, w, h, map);
    
    while (play(&bender, w, h, map)) {
        move(&bender);

        if (moves_idx >= ENDGAME) {
            printf("LOOP\n");
            return 0;
        }
    }

    int i=0;
    while (moves[i][0] != 0)
        printf("%s\n", moves[i++]);

    return 0;
}