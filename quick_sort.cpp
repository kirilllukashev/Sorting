#include<bits/stdc++.h>

using namespace std;


void quick_sort(int left, int right, vector<double> &arr) {
    int l_hold = left;
    int r_hold = right;
    double pivot = arr[left];
    while (left < right) {
        while ((arr[right] >= pivot) && (left < right))
            right--;
        if (left != right) {
            arr[left] = arr[right];
            left++;
        }
        while ((arr[left] <= pivot) && (left < right))
            left++;
        if (left != right) {
            arr[right] = arr[left];
            right--;
        }
    }
    arr[left] = pivot;
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        quick_sort(left, pivot - 1, arr);
    if (right > pivot)
        quick_sort(pivot + 1, right, arr);
}

int main(){
    int length = 1e5;
    for (int x = 0; x < 1; ++x) {
        vector<double> ans(length);
        for (int i = 0; i < length; ++i) {
            ans[i] = rand() % 1000000;
        }
        auto start = chrono::high_resolution_clock::now();
        quick_sort(0, length - 1, ans);
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = finish - start;
        cout << duration.count() << "\n";
    }
}
