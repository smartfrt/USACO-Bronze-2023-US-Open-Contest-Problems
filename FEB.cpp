#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    if (count(s.begin(), s.end(), 'F') == n) {
        s[0] = 'E';
    }

    vector<int> positions;
    for (int i = 0; i < n; i++) {
        if (s[i] != 'F') {
            positions.push_back(i);
        }
    }

    int prefix_f = positions[0];
    int suffix_f = n - 1 - positions.back();
    int ones = prefix_f + suffix_f;

    int mn = 0;
    int mx = 0;
    for (size_t i = 0; i < positions.size() - 1; i++) {
        int a = positions[i];
        int b = positions[i + 1];
        int gap = b - a;
        bool same_type = (s[a] == s[b]);
        mn += ((gap & 1) ^ (!same_type));  
        mx += gap - (!same_type);  
    }

    vector<int> ans;
    int start = mn;
    int end = ones + mx;
    int step = (ones == 0) ? 2 : 1;
    for (int i = start; i <= end; i += step) {
        ans.push_back(i);
    }

    cout << ans.size() << endl;
    for (int val : ans) {
        cout << val << endl;
    }

    return 0;
}