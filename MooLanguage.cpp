#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define sz(x) (int)x.size()

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, c, p;
        cin >> n >> c >> p;
        vector<string> nouns, tverb, iverb, conj;
        for (int i = 0; i < n; i++) {
            string w, t;
            cin >> w >> t;

            if (t == "noun") nouns.push_back(w);
            else if (t == "transitive-verb") tverb.push_back(w);
            else if (t == "intransitive-verb") iverb.push_back(w);
            else conj.push_back(w);
        }

        int ans = 0;
        int t1, t2, combine, tack_end;
        for (int type_1 = 0; type_1 <= sz(iverb); type_1++) {
            int noun_cnt = sz(nouns), conj_cnt = sz(conj);
            int period = p, comma = c;
            int cur_words = 0;

            cur_words += 2 * type_1;
            noun_cnt -= type_1;
            if (noun_cnt < 0) continue;

            int type_2 = min({sz(tverb), noun_cnt / 2, min(conj_cnt, period) * 2 + max(0, period - conj_cnt)});
            cur_words += 3 * type_2;
            noun_cnt -= 2 * type_2;

            int total = type_1 + type_2;
            int connections = type_1 + type_2 - 1;
            int can_combine = min((connections + 1) / 2, conj_cnt);
            cur_words += can_combine;
            period -= total - can_combine;
            if (period < 0) continue;

            int tack = 0;
            if (type_2 > 0) {
                tack = min(noun_cnt, comma);
                cur_words += tack;
            }
            if (cur_words > ans) {
                ans = cur_words;
                t1 = type_1;
                t2 = type_2;
                combine = can_combine;
                tack_end = tack;
            }
        }
        cout << ans << endl;

        if (ans == 0) {
            cout << endl;
            continue;
        }

        vector<vector<string>> sentences;
        for (int i = 0; i < t1; i++) {
            sentences.push_back({nouns.back(), iverb.back()});
            nouns.pop_back();
            iverb.pop_back();
        }
        for (int i = 0; i < t2; i++) {
            sentences.push_back({nouns.back(), tverb.back()});
            nouns.pop_back();
            tverb.pop_back();
            sentences.back().push_back(nouns.back());
            nouns.pop_back();
        }
        string output;
        for (int i = 0; i < sz(sentences); i++) {
            for (string j : sentences[i]) { output += j + " "; }
            if (i % 2 == 0 && combine) {
                combine--;
                output += conj.back() + " ";
                conj.pop_back();
            } else {
                output.pop_back();
                output += ". ";
            }
        }
        output.pop_back();
        if (tack_end > 0) {
            output.pop_back();
            for (int i = 0; i < tack_end; i++) {
                output += ", " + nouns.back();
                nouns.pop_back();
            }
            output += ".";
        }
        cout << output << endl;
    }
}