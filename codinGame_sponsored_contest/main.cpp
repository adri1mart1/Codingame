#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <array>

using namespace std;

// This game is a sort of pacman
// We have one character, and multiple ennemies
// Everyone is moving to a single tile at each run
// Seems like the best is to discover the whole map
//
// Things to do:
//  1 - Retrieve board info
//  2 - Be able to move in a direction, till a wall and then, go randomly
//  3 - Detect ennemy at a cell dist of 1
//

// Considering the map as follow:
//     0 1 2 3
//     ---------> X
//  0 |
//  1 |
//  2 |
//  3 |
//    Y
//

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STAY
};

static const map<Direction, string> direction_str {
    { LEFT,  "E" },
    { RIGHT, "A" },
    { UP,    "C" },
    { DOWN,  "D" },
    { STAY,  "B" }
};

static const map<Direction, string> direction_dbg_str {
    { LEFT,  "LEFT"  },
    { DOWN,  "DOWN"  },
    { UP,    "UP"    },
    { RIGHT, "RIGHT" }
};

class Character {
public:
    Character() :
        x(0), y(0), last_direction(UP) {}

    void set_direction(Direction d) {
        last_direction = d;
        cout << direction_str.at(d) << endl;
        cerr << "Going " << direction_dbg_str.at(d) << std::endl;
    }

    int x;
    int y;
    Direction last_direction;
};

class Tile {
public:

    Tile() : visited(false), type(UNKNOWN) {}

    enum Type {
        UNKNOWN,
        FREE,
        WALL,
        MYCHARACTER,
        ENNEMY
    };

    bool visited;
    Type type;
};

static const map<string, Tile::Type> tile_str {
    { "?", Tile::UNKNOWN },
    { "_", Tile::FREE },
    { "#", Tile::WALL },
    { "M", Tile::MYCHARACTER },
    { "E", Tile::ENNEMY }
};

static const map<Tile::Type, string> str_tile {
    { Tile::UNKNOWN,     "." },
    { Tile::FREE,        " " },
    { Tile::WALL,        "#" },
    { Tile::MYCHARACTER, "M" },
    { Tile::ENNEMY,      "E" }
};

class BoardMap {
public:
    BoardMap() {}

    void init(int x, int y) {
        this->x = x;
        this->y = y;
        map.resize(y);
        for (auto &line: map)
            line.resize(x);
    }

    Tile get_tile(int x, int y) {
        return map[y][x];
    }

    bool tile_has_ennemy_arround(int x, int y) {
        if (get_tile(x-1, y).type == Tile::ENNEMY ||
            get_tile(x, y-1).type == Tile::ENNEMY ||
            get_tile(x, y+1).type == Tile::ENNEMY ||
            get_tile(x+1, y).type == Tile::ENNEMY )
            return true;
        return false;
    }

    void dump() {
        cerr << "Map:" << endl << "    ";
        for (int i=0; i<x; i++)
                cerr << " " << i;
            cerr << endl;
        int j=0;
        for (auto &col: map) {
            cerr << setw(2) << j++ << " | ";
            for (auto &tile: col)
                cerr << str_tile.at(tile.type) << " ";
            cerr << endl;
        }
    }

    void set_sight(int x, int y, string l, string b, string r, string t) {
        map[y][x].type = Tile::MYCHARACTER;
        map[y][x].visited = true;
        map[y][x-1].type = tile_str.at(l);
        map[y+1][x].type = tile_str.at(b);
        map[y][x+1].type = tile_str.at(r);
        map[y-1][x].type = tile_str.at(t);
    }

    void set(int x, int y, Tile::Type t) {
        // cerr << "set x:" << x << " y:" << y << endl;
        map[y][x].type = t;
    }

    vector<vector<Tile>> map;
    int x, y;
};

class Board {
public:
    Board() {}

    void play() {

        if (can_go(me.last_direction, false)) {
            cerr << "can continue" << endl;
            me.set_direction(me.last_direction);
        } else {
            // check for unvisited
            if (can_go(LEFT, true)) {
                cerr << "can go left 1" << endl;
                me.set_direction(LEFT);
            } else if (can_go(UP, true)) {
                cerr << "can go up 1" << endl;
                me.set_direction(UP);
            } else if (can_go(RIGHT, true)) {
                cerr << "can go right 1" << endl;
                me.set_direction(RIGHT);
            } else if (can_go(DOWN, true)) {
                cerr << "can go down 1" << endl;
                me.set_direction(DOWN);
            } else {

                // check for any free one
                std::array<Direction, 4> arr {LEFT, UP, RIGHT, DOWN};
                std::random_shuffle(arr.begin(), arr.end());

                bool found = false;
                for (auto &i: arr) {
                    if (can_go(i, false)) {
                        cerr << "can go " << direction_str.at(i) << endl;
                        me.set_direction(i);
                        found = true;
                        break;
                    }
                }
                if (found == false)
                    cout << direction_str.at(STAY) << endl;
            }
        }
    }

    void init() {
        ennemy_number = character_number - 1;
        ennemies.resize(ennemy_number);
        map.init(X, Y);
    }

    bool can_go(Direction d, bool must_be_unvisited) {
        switch (d) {
            case LEFT:
                if (map.get_tile(me.x-1, me.y).type == Tile::FREE &&
                    map.tile_has_ennemy_arround(me.x-1, me.y) == false) {
                    if (must_be_unvisited) {
                        if (map.get_tile(me.x-1, me.y).visited == false)
                            return true;
                        else
                            return false;
                    }
                    return true;
                }
            break;
            case RIGHT:
                if (map.get_tile(me.x+1, me.y).type == Tile::FREE &&
                    map.tile_has_ennemy_arround(me.x+1, me.y) == false) {
                    if (must_be_unvisited) {
                        if (map.get_tile(me.x+1, me.y).visited == false)
                            return true;
                        else
                            return false;
                    }
                    return true;
                }
            break;
            case UP:
                if (map.get_tile(me.x, me.y-1).type == Tile::FREE &&
                    map.tile_has_ennemy_arround(me.x, me.y-1) == false) {
                    if (must_be_unvisited) {
                        if (map.get_tile(me.x, me.y-1).visited == false)
                            return true;
                        else
                            return false;
                    }
                    return true;
                }
            break;
            case DOWN:
                if (map.get_tile(me.x, me.y+1).type == Tile::FREE &&
                    map.tile_has_ennemy_arround(me.x, me.y+1) == false) {
                    if (must_be_unvisited) {
                        if (map.get_tile(me.x, me.y+1).visited == false)
                            return true;
                        else
                            return false;
                    }
                    return true;
                }
            break;
            default:
                break;
        }
        return false;
    }

    void set_character(int idx, int x, int y) {
        if (idx == ennemy_number) {
            me.x = x;
            me.y = y;
        } else {
            map.set(ennemies[idx].x, ennemies[idx].y, Tile::FREE);
            ennemies[idx].x = x;
            ennemies[idx].y = y;
            map.set(x, y, Tile::ENNEMY);
        }
    }

    void set_sight(string l, string b, string r, string t) {
        map.set_sight(me.x, me.y, l, b, r, t);
    }

    void dump() {
        cerr << "Board size X:" << X << " Y:" << Y << endl;
        cerr << "Number of ennemies:" << ennemy_number << endl;
        for (auto &e: ennemies)
            cerr << "Ennemy X:" << e.x << " Y:" << e.y << endl;
        cerr << "My character: X:" << me.x << " Y:" << me.y << endl;

        map.dump();
    }

    Character me;
    vector<Character> ennemies;
    int X;
    int Y;
    int character_number;
    int ennemy_number;
    BoardMap map;
};

int main()
{
    Board board;
    cin >> board.Y; cin.ignore();
    cin >> board.X; cin.ignore();
    cin >> board.character_number; cin.ignore();
    board.init();

    while (1) {
        string left, bottom, right, top;

        getline(cin, top);
        getline(cin, right);
        getline(cin, bottom);
        getline(cin, left);

        for (int i = 0; i < board.character_number; i++) {
            int x, y;
            cin >> x >> y; cin.ignore();
            board.set_character(i, x, y);
        }

        // cerr << "C: Left:" << left << " Bottom:" << bottom << " Right:" << right << " Top:" << top << endl;
        board.set_sight(left, bottom, right, top);
        board.dump();
        board.play();
    }

    return 0;
}
