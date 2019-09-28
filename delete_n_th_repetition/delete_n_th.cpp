#include "delete_n_th.h"
#include <algorithm>
#include <unordered_set>

std::vector<int> deleteNth(std::vector<int> arr, int n) {
  std::unordered_set<int> s{arr.begin(), arr.end()};
  for (auto e : s) {
    int counter{0};
    arr.erase(std::remove_if(arr.begin(), arr.end(),
                             [n, e, &counter](int current) {
                               if (e == current) {
                                 ++counter;
                                 return counter > n;
                               } else
                                 return false;
                             }),
              arr.end());
  }
  return arr;
}
