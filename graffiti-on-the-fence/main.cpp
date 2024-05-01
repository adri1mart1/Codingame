#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

struct interval {
    int a;
    int b;
};

[[nodiscard]] bool is_in_interval(const struct interval interval, const struct interval to_check)
{
    assert(interval.a <= interval.b);
    assert(to_check.a <= to_check.b);

    if (to_check.b <= interval.a || to_check.a >= interval.b)
        return false;
    return true;
}

int main()
{
    vector<int> sections;
    vector<struct interval> intervals;
    bool all_painted = true;
    sections.push_back(0);

    int l;
    cin >> l; cin.ignore();
    int n;
    cin >> n; cin.ignore();
    for (int i=0; i<n; ++i) {
        int st, ed;
        cin >> st >> ed; cin.ignore();
        sections.push_back(st);
        sections.push_back(ed);
        intervals.push_back({st, ed});
    }
    sections.push_back(l);
    sort(sections.begin(), sections.end());

    for (int i=0; i<sections.size()-1; ++i) {
        // ignore intervals that are not intervals (ex: [4;4])
        if (sections[i] == sections[i+1])
            continue;

        const struct interval iv = {sections[i], sections[i+1]};
        bool iv_in_interval = false;

        for (int j=0; j<intervals.size() && !iv_in_interval; ++j) {
            if (is_in_interval(intervals[j], iv))
                iv_in_interval = true;
        }

        if (!iv_in_interval) {
            cout << iv.a << " " << iv.b << endl;
            all_painted = false;
        }
    }

    if (all_painted)
        cout << "All painted" << endl;

    return 0;
}
