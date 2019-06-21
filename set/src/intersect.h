#ifndef SET_SRC_INTERSECT_H_
#define SET_SRC_INTERSECT_H_

#include <string>
#include <vector>
#include <algorithm>
  
std::vector<std::string> GetSortedElementsOfFirstInSecond(std::vector<std::string> first, std::vector<std::string> second)
{
  std::vector<std::string> common_elements;
  std::sort(first.begin(), first.end());
  std::sort(second.begin(), second.end());
  std::set_intersection(first.cbegin(), first.cend(),
                 second.cbegin(), second.cend(),
                 std::back_inserter(common_elements));

  return common_elements;
}


#endif //SET_SRC_INTERSECT_H_
