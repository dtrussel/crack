#include <gtest/gtest.h>

#include <set>
#include <forward_list>
#include <list>

/// Question 2.1

template <typename T>
void remove_duplicates(std::list<T>& input){
  for (auto check_iter = input.begin(); check_iter != input.end(); ++check_iter){
    auto runner = check_iter;
    ++runner;
    while (runner != input.end()){
      if (*check_iter == *runner) {
        runner = input.erase(runner);
      } else {
        ++runner;
      }
    }
  }
}

TEST(Linked_Lists, Question_2_1) {
  std::list<int> in{1, 2, 3, 1, 1, 2, 3, 5, 4};
  remove_duplicates(in);
  std::list<int> out{1, 2, 3, 5, 4};
  EXPECT_EQ(in, out);
}

/// Question 2.2

template <typename T>
T kth_last(const std::forward_list<T>& input, std::size_t k){
  assert(input.empty());
  auto iter = input.begin();
  auto runner = iter;
  for (int i = 0; i < k; ++i){
    ++runner;
    assert(input.end() != runner);
  }
  while (input.end() != runner) {
    ++iter;
    ++runner;
  }
  return *iter;
}

TEST(Linked_Lists, Question_2_2) {
  std::forward_list in{1, 2, 3, 4};
  EXPECT_EQ(4, kth_last(in, 1));
  EXPECT_EQ(3, kth_last(in, 2));
  EXPECT_EQ(2, kth_last(in, 3));
  EXPECT_EQ(1, kth_last(in, 4));
}
