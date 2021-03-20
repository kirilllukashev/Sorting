#include<bits/stdc++.h>

using namespace std;

void radix_sort(std::vector<double>& vec) {
  std::vector<double> tmp(vec.size());
  // sort by m
  for (int i = 0; i < 4; ++i) {
    std::vector<int> cnt_m(1 << 13);
    if (i % 2 == 0) {
      for (auto num : vec) {
        uint64_t bits = *reinterpret_cast<const uint64_t*>(&num);
        uint64_t m = bits << (64 - 13 * (i + 1)) >> 51;
        cnt_m[m]++;
      }
      for (int i = 1; i < 1 << 13; ++i)
        cnt_m[i] += cnt_m[i - 1];
      for (auto num : vec) {
        uint64_t bits = *reinterpret_cast<const uint64_t*>(&num);
        uint64_t m = bits << (64 - 13 * (i + 1)) >> 51;
        tmp[--cnt_m[m]] = num;
      }

      std::reverse(tmp.begin(), tmp.end());
    }
    else {
      for (auto num : tmp) {
        uint64_t bits = *reinterpret_cast<const uint64_t*>(&num);
        uint64_t m = bits << (64 - 13 * (i + 1)) >> 51;
        cnt_m[m]++;
      }
      for (int i = 1; i < 1 << 13; ++i)
        cnt_m[i] += cnt_m[i - 1];
      for (auto num : tmp) {
        uint64_t bits = *reinterpret_cast<const uint64_t*>(&num);
        uint64_t m = bits << (64 - 13 * (i + 1)) >> 51;
        vec[--cnt_m[m]] = num;
      }

      std::reverse(vec.begin(), vec.end());
    }
  }
  // sort by p
  std::vector<int> cnt_p(1 << 11, 0);
  for (auto num : vec) {
    uint64_t bits = *reinterpret_cast<const uint64_t*>(&num);
    std::bitset<64> debug = std::bitset<64>(*reinterpret_cast<const uint64_t*>(&num));
    int64_t p = (bits << 1 >> 53);
    cnt_p[p]++;
  }
  for (int i = 1; i < 1 << 11; ++i) {
    cnt_p[i] += cnt_p[i - 1];
  }
  for (auto num : vec) {
    uint64_t bits = *reinterpret_cast<const uint64_t*>(&num);
    uint64_t p = bits << 1 >> 53;
    tmp[--cnt_p[p]] = num;
  }

  std::reverse(tmp.begin(), tmp.end());
  // sort by m sign
  std::vector<int> m_sign_count(2, 0);
  for (auto num : tmp) {
    uint64_t bits = *reinterpret_cast<const uint64_t*>(&num);
    int64_t m = bits >> 63;
    m_sign_count[(m + 1) % 2]++;
  }
  m_sign_count[1] += m_sign_count[0];
  for (auto num : tmp) {
    uint64_t bits = *reinterpret_cast<const uint64_t*>(&num);
    int64_t m = bits >> 63;
    vec[--m_sign_count[(m + 1) % 2]] = num;
  }
  auto neg_end = std::lower_bound(vec.begin(), vec.end(), 0.0);
  std::reverse(vec.begin(), neg_end);
  return;
}

int main() {
    int length = 1e7;
    for (int x = 0; x < 10; ++x) {
        vector<double> ans(length);
        for (int i = 0; i < length; ++i) {
            ans[i] = rand() % 1000000 / 100.0;
        }
        auto start = chrono::high_resolution_clock::now();
        radix_sort(ans);
        auto finish = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = finish - start;
        cout << duration.count() << "\n";
    }
}
