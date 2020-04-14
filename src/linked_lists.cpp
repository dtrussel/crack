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

/// Question 2.4

std::list<int> partition(const std::list<int>& input, int value){
  std::list<int> ret{value};
  for (auto entry : input) {
    if (entry >= value) { ret.emplace_back(entry); }
    else { ret.emplace_front(entry); }
  }
  return ret;
}

TEST(Linked_Lists, Question_2_4){
  EXPECT_EQ(partition({3, 7, 10, 6, 3, 2}, 4), std::list({2, 3, 3, 4, 7, 10, 6}));
}

/// Question 2.5

int list_to_number(const std::list<int>& in){
  int ret = 0;
  int multiplier = 1;
  for (auto val : in) {
    ret += val * multiplier;
    multiplier *= 10;
  }
  return ret;
}

std::list<int> number_to_list(int num){
  std::list<int> ret;
  constexpr int divider = 10;
  while (num) {
    ret.emplace_back(num % divider);
    num /= divider;
  }
  return ret;
}

std::list<int> sum(const std::list<int>& alpha, const std::list<int>& beta){
  const int sum = list_to_number(alpha) + list_to_number(beta);
  return number_to_list(sum);
}

TEST(Linked_Lists, Question_2_5){
  EXPECT_EQ(sum({7, 1, 6}, {5, 9, 2}), std::list({2, 1, 9}));
}
