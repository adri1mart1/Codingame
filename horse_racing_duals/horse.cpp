#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int N, d = 999999;
    vector<int> v;
    cin >> N; cin.ignore();
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        v.push_back(Pi);
    }

    sort(v.begin(), v.end());

    for (int i=1; i<N; i++) {
        int t = abs(v[i] - v[i-1]);
        if (t < d)
            d = t;
    }

    cout << d << endl;
}