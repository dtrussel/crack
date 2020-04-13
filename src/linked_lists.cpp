#include <gtest/gtest.h>

#include <set>
#include <list>

/// Question 2.1

void remove_duplicates(std::list<int>& input){
  for (auto check_iter = input.begin(); check_iter != input.end(); ++check_iter){
    auto runner = check_iter;
    ++runner;
    for (; runner != input.end(); ++runner){
      if (*check_iter == *runner) {
        input.erase(runner);
      }
    }
  }
}

TEST(Linked_Lists, Question_2_1) {
  std::list<int> in = {1, 2, 3, 1, 1, 2, 3, 5, 4};
  remove_duplicates(in);
  std::list<int> out = {1, 2, 3, 5, 4};
  EXPECT_EQ(in, out);
}
