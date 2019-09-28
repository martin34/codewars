#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "delete_n_th_repetition/delete_n_th.h"
#include <iostream>

using namespace ::testing;

TEST(DeleteNth, WhenNoDublicatesThanReturnFullArray) {
  std::vector<int> a{1, 2, 3};
  auto res = deleteNth(a, 1);
  EXPECT_THAT(res, Eq(a));
}
TEST(DeleteNth, WhenOneDublicateThanRemoveIt) {
  std::vector<int> a{1, 1, 2, 3};
  auto res = deleteNth(a, 1);
  std::vector<int> expect{1, 2, 3};
  EXPECT_THAT(res, Eq(expect));
}
TEST(DeleteNth, WhenN2OneElementToRemoveThanRemoveIt) {
  std::vector<int> a{1, 1, 2, 2, 2, 3};
  auto res = deleteNth(a, 2);
  std::vector<int> expect{1, 1, 2, 2, 3};
  EXPECT_THAT(res, Eq(expect));
}
