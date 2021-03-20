#include<bits/stdc++.h>

using namespace std;

struct heap {
    vector<double> tree;
    heap(){
        tree.push_back(0);
    }
    void push(double x){
        tree.push_back(x);
        sift_up(tree.size() - 1);
    }
    int top(){
        if(tree.size() != 1){
            return tree[1];
        }
    }
    void pop(){
        if(tree.size() != 1){
            tree[1] = tree.back();
            tree.pop_back();
            sift_down(1);
        }
    }
    void sift_up(int v){
        if (v == 1) return;
        if(tree[v / 2] > tree[v]){
            swap(tree[v / 2], tree[v]);
            sift_up(v / 2);
        }
    }
    void sift_down(int v) {
        if (v * 2 >= tree.size()){
            return;
        }
        int max_ind;
        if (v * 2 + 1 == tree.size()){
                max_ind = v * 2;
        }
        else if (tree[v * 2] <= tree[v * 2 + 1]){
             max_ind = v * 2;
        }
        else {
            max_ind = v * 2 + 1;
        }

        if (tree[v] > tree[max_ind]) {
            swap(tree[v], tree[max_ind]);
            sift_down(max_ind);
        }
    }
};

void heap_sort(vector<double> &ans) {
    heap sorting;
    for (int i = 0; i < ans.size(); ++i) {
        sorting.push(ans[i]);
    }
    int val;
    for (int i = 0; i < ans.size(); ++i) {
        val = sorting.top();
        sorting.pop();
        ans[i] = val;
        //cout << ans[i] << ' ';
    }
}
int main() {
    int length = 1e5;
    for (int x = 0; x < 10; ++x) {
        vector<double> ans(length);
        for (int i = 0; i < length; ++i) {
            ans[i] = rand() % 1000000;
        }
        auto start = chrono::high_resolution_clock::now();
        heap_sort(ans);
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = finish - start;
        cout << duration.count() << "\n";
    }
}
