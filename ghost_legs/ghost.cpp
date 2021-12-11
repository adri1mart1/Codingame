#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int W;
    int H;
    cin >> W >> H; cin.ignore();
    vector<vector<char>> v(H, vector<char>(W));

    for (int i = 0; i < H; i++) {
        string line;
        getline(cin, line);
        int j=0;
        for (string::const_iterator it = line.begin(); it != line.cend(); ++it) {
            v[i].at(j) = *it;
            j++;
        }
    }

    for (int col=0; col<W; col+=3) {
        int y = col;
        cout << v[0][y];
        for (int x=1; x<H; x++) {
            if (v[x][y] != '|') {
                cout << v[x][y] << endl;
            } else {
                if ((y-1 > 0) && (v[x][y-1] == '-')) {
                    y -= 3;
                    continue;
                }
                if ((y+1 < W) && (v[x][y+1] == '-'))
                    y += 3;
            }
        }
    }
}