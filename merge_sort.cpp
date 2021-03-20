#include<bits/stdc++.h>

using namespace std;

const int length = 1e5;

vector<double> memory_buffer(length + 10);

void merge_arr(vector<double> &ans, int l, int m, int r){
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (ans[i] <= ans[j]) {
            memory_buffer[k] = ans[i];
            ++i;
        } else {
            memory_buffer[k] = ans[j];
            ++j;
        }
        ++k;
    }
    while (i < m) {
        memory_buffer[k] = ans[i];
        ++i;
        ++k;
    }
    while (j < r) {
        memory_buffer[k] = ans[j];
        ++j;
        ++k;
    }

    for (int x = l; x < r; ++x) {
        ans[x] = memory_buffer[x];
    }
}

void merge_sort(vector<double> &ans, int l, int r) {
    if (r - l <= 1) {
        return;
    }
    int m = l + (r - l) / 2;
    merge_sort(ans, l, m);
    merge_sort(ans, m, r);
    merge_arr(ans, l, m, r);
}

int main(){
    for (int x = 0; x < 10; ++x) {
        vector<double> ans(length);
        for (int i = 0; i < length; ++i) {
            ans[i] = rand() % 1000000;
        }
        auto start = chrono::high_resolution_clock::now();
        merge_sort(ans, 0, length);
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = finish - start;
        cout << duration.count() << "\n";
    }
}

