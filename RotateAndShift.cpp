#include <iostream>

using namespace std;
 
const int mx = 200005;
int A[mx];
int ans[mx];

int main(){
    int n, k, t; 
    cin >> n >> k >> t;
    for(int i = 1; i <= k; i++) {
        cin >> A[i];
    }
    A[k + 1] = n;
    for(int i = 1; i <= k; i++){
        for(int j = A[i]; j < A[i + 1]; j++){
            int current_shift = j - A[i];
            int new_shift = current_shift-t;
            int diff = A[i + 1 ]- A[i];
            new_shift = (new_shift % diff + diff) % diff; 
            
            ans[(A[i] + new_shift + t) % n] = j;
        }
    }
    for(int i = 0; i < n; i++){
        cout << ans[i];
        if(i + 1 < n) cout << " ";
    }
    cout << endl;
}